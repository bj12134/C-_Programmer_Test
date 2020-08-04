#pragma once

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include "httplib.h"

class FileUtil {
public:
	// 从文件中读取所有内容
	static bool Read(const std::string& name, std::string* body) {
		std::ifstream fs(name, std::ios::binary);
		if (fs.is_open() == false) {
			std::cout << "ifstream " << name << "open failed\n";
			return false;
		}
		// boost::filesystem::file_size()获取文件大小
		int64_t fsize = boost::filesystem::file_size(name);
		body->resize(fsize);
		fs.read(&(*body)[0], fsize);
		if (fs.good() == false) {
			std::cout << "read " << name << "failed\n";
			return false;
		}
		fs.close();
		return true;
	}
	// 向文件中写入数据
	static bool Write(const std::string& name, const std::string& body) {
		std::ofstream ofs(name, std::ios::binary);
		if (ofs.is_open() == false) {
			std::cout << "open " << name << "failed\n";
			return false;
		}
		ofs.write(&body[0], body.size());
		if (ofs.good() == false) {
			std::cout << "write " << name << "failed\n";
			return false;
		}
		ofs.close();
		return 0;
	}
};




class DataManage {
public:
	DataManage(const std::string& filename) 
		:_store_file(filename)
	{}
	bool Insert(const std::string& key, const std::string& val) {
		_backup_list[key] = val;
		return true;
	}
	bool GetEtag(const std::string& key, std::string* val){
		auto it = _backup_list.find(key);
		if (it == _backup_list.end())
			return false;
		*val = it->second;
		return true;
	}
	bool Storage() {
		std::stringstream tmp;
		auto it = _backup_list.begin();
		for (; it != _backup_list.end(); ++it) {
			tmp << it->first << " " << it->second << "\r\n";
		}
		FileUtil::Write(_store_file, tmp.str());
	}
	bool InitLoad() {
		// 1.将备份信息从文件中读取
		// 2.按照"\r\n"进行字符分割 -- key(源文件名称),val(压缩包名称)
		// 3.将<key, val>插入到_file_list中x
		std::string body;
		if (FileUtil::Read(_store_file, &body) == false) {
			return false;
		}
		std::vector<std::string> list;
		boost::split(list, body, boost::is_any_of("\r\n"), boost::token_compress_off);
		for (auto it : list) {
			size_t pos = it.find(" ");
			if (pos == std::string::npos) {
				continue;
			}
			std::string key = it.substr(0, pos);
			std::string val = it.substr(pos + 1);
			Insert(key, val);
		}
		return true;
	}
private:
	std::string _store_file;	// 持久化存储文件名称
	std::unordered_map<std::string, std::string> _backup_list; // 备份的文件信息
};
#define STORE_FILE "./list.backup"
#define LISTEN_FILE "./backup/"
class CloudClient {
public:
	CloudClient(const std::string& dirname, const std::string& store_file,
		const std::string& ip, const uint16_t& port)
		:_listen_dir(dirname),
		_data_manage(store_file),
		_srv_ip(ip),
		_srv_port(port)
	{}
	bool Start() {
		_data_manage.InitLoad();
		while (1) {
			std::vector<std::string> list;
			GetBackupFileList(&list);
			for (int i = 0; i < list.size(); ++i) {
				std::string filename = list[i];
				std::string pathname = _listen_dir + filename;
				std::string body;
				FileUtil::Read(pathname, &body);
				httplib::Client client(_srv_ip, _srv_port);
				std::string req_path = "/" + filename;
				auto rsp = client.Put(req_path.c_str(), body, "application/octet-stream");
				if (rsp == NULL || (rsp != NULL && rsp->status != 200)) {
					continue;
				}
				std::string etag;
				GetEtag(pathname, &etag);
				_data_manage.Insert(filename, etag);
				std::cout << pathname << "backup success!\n";
			}
			Sleep(1000);
		}
	}
	bool GetBackupFileList(std::vector<std::string>* list) {
		boost::filesystem::directory_iterator begin(_listen_dir);
		boost::filesystem::directory_iterator end;
		for (; begin != end; ++begin) {
			if (boost::filesystem::is_directory(begin->status())) {
				continue;
			}
			std::string pathname = begin->path().string();
			std::string filename = begin->path().filename().string();
			std::string cur_etag, old_etag;
			GetEtag(pathname, &cur_etag);
			_data_manage.GetEtag(filename, &old_etag);
			if (cur_etag != old_etag) {
				list->push_back(filename);
			}
		}
		return true;
	}
	bool GetEtag(const std::string& pathname, std::string* etag) {
		int64_t fsize = boost::filesystem::file_size(pathname);
		time_t mtime = boost::filesystem::last_write_time(pathname);
		*etag = std::to_string(fsize) + "-" + std::to_string(mtime);
		return true;
	}
private:
	std::string _listen_dir;	// 监控的目录的名称
	DataManage _data_manage;
	std::string _srv_ip;
	uint16_t _srv_port;
};