#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <zlib.h>
#include "httplib.h"
#include <pthread.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#define BACKUP_DIR "./backup/"  // 文件的备份路径
#define GZFILE_DIR "./gzfile/"  // 文件的压缩路径
#define DATA_FILE "./list.backup" // 数据管理模块的数据备份文件名称

namespace _cloud_sys{

#define NONHOT_TIME 10   // 非热点文件基准值
#define INTERVAL_TIME 5 // 非热点文件检测时间

  class FileUtil{
    public:
      // 从文件中读取所有内容
      static bool Read(const std::string& name, std::string* body){
        std::ifstream fs(name, std::ios::binary);
        if(fs.is_open() == false){
          std::cout << "ifstream " << name << "open failed\n";
          return false;
        }
        // boost::filesystem::file_size()获取文件大小
        int64_t fsize = boost::filesystem::file_size(name);
        body->resize(fsize);
        fs.read(&(*body)[0], fsize);
        if(fs.good() == false){
          std::cout << "read " << name << "failed\n";
          return false;
        }
        fs.close();
        return true;
      }
      // 向文件中写入数据
      static bool Write(const std::string& name, const std::string& body){
        std::ofstream ofs(name, std::ios::binary);
        if(ofs.is_open() == false){
          std::cout << "open " << name << "failed\n";
          return false;
        }
        ofs.write(&body[0], body.size());
        if(ofs.good() == false){
          std::cout << "write " << name << "failed\n";
          return false;
        }
        ofs.close();
        return 0;
      }
  };
  class CompressUtil{
    public:
      // 文件压缩(源文件名称, 压缩文件名称)
      static bool Compress(const std::string& src, const std::string& dst){
        std::string body;
        FileUtil::Read(src, &body);

        gzFile gf = gzopen(dst.c_str(), "wb");
        if(gf == NULL){
          std::cout << "gzopen " << dst << "failed\n";
          return false;
        }
        unsigned int wlen = 0;
        while(wlen < body.size()){
          int ret = gzwrite(gf, &body[wlen], body.size() - wlen);
          if(ret == 0){
            std::cout << "gzwrite " << dst << "failed\n";
            return false;
          } 
          wlen += ret;
        }
        gzclose(gf);
        return true;
      }
      // 文件解压(压缩文件名称, 源文件名称)
      static bool UnCompress(const std::string& src, const std::string& dst){
        std::ofstream ofs(dst, std::ios::binary);
        if(ofs.is_open() == false){
          std::cout << "ofstream " << dst << "failed\n";
          return false;
        }
        gzFile gf = gzopen(src.c_str(), "rb");
        if(gf == NULL){
          std::cout << "gzopen " << src << "failed\n";
          return false;
        }
        char tmp[4096] = {0};
        int ret = 0;
        int wlen = 0;
        while((ret = gzread(gf, tmp, 4096)) > 0){
          wlen += ret;
          ofs.write(tmp, ret);
        }
        ofs.close();
        gzclose(gf);
        return true;
      }
  };
  
  class DataManage{
    public:
      DataManage(const std::string& path)
        :_back_file(path)
      {
        pthread_rwlock_init(&_rwlock, NULL);
      }
      ~DataManage(){
        pthread_rwlock_destroy(&_rwlock);
      }
      // 判断文件是否存在
      bool Exists(const std::string& filename){
        // 从_file_list找到filename的文件信息
        pthread_rwlock_rdlock(&_rwlock);
        auto it = _file_list.find(filename);
        if(it == _file_list.end()){
          pthread_rwlock_unlock(&_rwlock);
          return false;
        }
        pthread_rwlock_unlock(&_rwlock);
        return true;
      }
      // 判断文件是否已经被压缩
      bool IsCompress(const std::string& filename){
        // 管理的数据:源文件名称 压缩包名称\r\n
        // 文件上传后:源文件名称和压缩包名称一致
        // 文件压缩后:将压缩包名称更新为具体的名称
        pthread_rwlock_rdlock(&_rwlock);
        auto it = _file_list.find(filename);
        if(it == _file_list.end()){
          pthread_rwlock_unlock(&_rwlock);
          return false;
        }
        if(it->first == it->second){
          pthread_rwlock_unlock(&_rwlock);
          return false;
        }
        pthread_rwlock_unlock(&_rwlock);
        return true;
      }
      // 获取未压缩文件列表
      bool NonCompressList(std::vector<std::string>* list){
        // 遍历_file_list,查找到没有压缩的文件名称并插入到list中
        pthread_rwlock_rdlock(&_rwlock);
        auto it = _file_list.begin();
        for( ; it != _file_list.end(); ++it){
          if(it->first == it->second){
            list->push_back(it->first);
          }
        }
        pthread_rwlock_unlock(&_rwlock);
        return true;
      }
      // 插入更新数据
      bool Insert(const std::string& src, const std::string& dst){
        pthread_rwlock_wrlock(&_rwlock);
        _file_list[src] = dst;
        pthread_rwlock_unlock(&_rwlock);
        Storage();
        return true;
      }
      // 获取所有文件名称
      bool GetAllFileName(std::vector<std::string>* list){
        pthread_rwlock_rdlock(&_rwlock);
        auto it = _file_list.begin();
        for( ; it != _file_list.end(); ++it){
          list->push_back(it->first);
        }
        pthread_rwlock_unlock(&_rwlock);
        return true;
      }
      // 根据源文件名称获取压缩包名称
      bool GetGzName(const std::string& src, std::string* dst){
        auto it = _file_list.find(src);
        if(it == _file_list.end())
          return false;
        *dst = it->second;
        return true;
      }
      // 数据改变后持久化存储
      bool Storage(){
        std::stringstream tmp;
        pthread_rwlock_rdlock(&_rwlock);
        auto it = _file_list.begin();
        for( ;it != _file_list.end(); ++it){
          tmp << it->first << " " << it->second << "\r\n";
        }
        pthread_rwlock_unlock(&_rwlock);
        FileUtil::Write(_back_file, tmp.str());
        return true;
      }
      // 启动时初始化加载原有数据
      // #include <boost/algorithm/string.hpp>
      // boost::split() -- (vector, src, boost::is_any_of(sep), flag)
      // src:要解析的字符串
      // sep:分割字符
      // flag:boost::token_compress_off/on 不保存 / 保存 分割字符
      bool InitLoad(){
       // 1.将备份信息从文件中读取
       // 2.按照"\r\n"进行字符分割 -- key(源文件名称),val(压缩包名称)
       // 3.将<key, val>插入到_file_list中
        std::string body;
        if(FileUtil::Read(_back_file, &body) == false){
          return false;
        }
        std::vector<std::string> list;
        boost::split(list, body, boost::is_any_of("\r\n"), boost::token_compress_off);
        for(auto it : list){
          size_t pos = it.find(" ");
          if(pos == std::string::npos){
            continue;
          }
          std::string key = it.substr(0, pos);
          std::string val = it.substr(pos + 1);
          Insert(key, val);
        }
      return true;
      }
    private:
      std::string _back_file; // 持久化存储数据的文件名称
      std::unordered_map<std::string, std::string> _file_list;  // 文件列表:源文件名称-压缩包名称
      pthread_rwlock_t _rwlock;
  };
  DataManage data_manage(DATA_FILE);
  class NonHotCompresss{
    public:
      NonHotCompresss(const std::string& bu_dir, const std::string& gz_dir)
        :_bu_dir(bu_dir),
        _gz_dir(gz_dir)
      {}
    public:
      // 总体向外提供的接口功能,开始压缩模块
      void Start(){
        // 每隔一段时间判断是否有非热点文件存在
        // 非热点文件判断基准问题:当前时间减去最后一次访问时间 > 基准值
        while(1){
          // 1.获取所有未压缩的的文件名称
          // 2.逐个判断该文件是否为热点文件
          // 3.如果是则压缩,并删除源文件
          // 4.操作结束,休眠一段时间
          std::vector<std::string> list;
          data_manage.NonCompressList(&list);
          size_t i = 0;
          for( ; i < list.size(); ++i){
            if(FileIsHot(list[i]) == false){
              printf("file [%s] is NoHotFile\n", list[i].c_str()); 
              std::string s_filename = list[i];
              std::string d_filename = list[i] + ".gz";
              std::string src_name = BACKUP_DIR + s_filename;
              std::string dst_name = GZFILE_DIR + d_filename;
              if(CompressUtil::Compress(src_name, dst_name) == true){
                data_manage.Insert(s_filename, d_filename);
                printf("file [%s] compress success!\n", list[i].c_str());
                unlink(src_name.c_str());
              }
            }
          }
          sleep(INTERVAL_TIME);
        }
      }
    private:
      // 判断一个文件是否为热点文件
      bool FileIsHot(const std::string& filename){
        time_t cur_time = time(NULL); // 获取当前时间
        struct stat st;
        if(stat(filename.c_str(), &st) < 0){
          std::cout << "get file " << filename << " failed\n";
          return false;
        }
        if((cur_time - st.st_atime) > NONHOT_TIME){
          return false;
        }
        return true;
      }
    private:
      std::string _bu_dir;  // 压缩前文件的存储路径
      std::string _gz_dir;  // 压缩后文件的存储路径
  };
  class Server{
    public:
      // 启动网络通信模块接口
      bool Start(){
        data_manage.InitLoad();
        _server.Put("/(.*)", FileUpLoad); // 上传请求
        _server.Get("/list", List); // 列表请求
        // 正则表达式:.*表示匹配任意字符串 ()表示捕捉这个字符串
        _server.Get("/download/(.*)", FileDownLoad); // 下载请求
        _server.listen("0.0.0.0", 9000);  // 搭建tcp服务器,进行http数据接收处理
        return true;
      }
    private: 
      // 文件上传处理回调函数
      static void FileUpLoad(const httplib::Request& req, httplib::Response& rsp){
        std::cout << "Accention Success!\n";
        // set_content(正文数据, 数据长度, 正文类型)
        // matches[0] -- Get到的所有字符串, matches[1] -- 捕捉到的字符串
        std::string filename = req.matches[1];  // 纯文件名称
        std::string pathname = BACKUP_DIR + filename; // 组织文件路径名,将文件备份到指定目录
        FileUtil::Write(pathname, req.body);  // 向文件中写入数据
        data_manage.Insert(filename, filename); // 添加文件名称到数据管理模块
        rsp.status = 200;
        return;
      }
      // 文件列表处理回调函数
      static void List(const httplib::Request& req, httplib::Response& rsp){
        std::vector<std::string> list;
        std::cout << "list requeset success\n";
        data_manage.GetAllFileName(&list);
        std::stringstream tmp;
        tmp << "<html>";
        tmp << "<head>File_List</head>"
        tmp << "<body><hr />";
        size_t i = 0;
        for(; i < list.size(); ++i){
          tmp << "<a href='/download/>" << list[i] << "'>" << list[i] << "</a>";
          tmp << "hr /";
        }
        tmp << "<hr /></body>";
        tmp << "/html>";
        // std::cout << "body \n[" << tmp.str().c_str() << "]\n";
        rsp.set_content(tmp.str().c_str(), tmp.str().size(), "text/html");
        rsp.status = 200;
      }
      // 文件下载处理回调函数
      static void FileDownLoad(const httplib::Request& req, httplib::Response& rsp){
        std::string filename = req.matches[1];
        if(data_manage.Exists(filename) == false){
          rsp.status = 404; // 文件不存在,返回错误码
          return;
        }
        std::string pathname = BACKUP_DIR + filename;
        if(data_manage.IsCompress(filename)){
          std::string gzfile;
          data_manage.GetGzName(filename, &gzfile);
          std::string gzpathname = GZFILE_DIR + gzfile;
          CompressUtil::UnCompress(gzpathname, pathname);
          unlink(gzpathname.c_str()); // 删除压缩包
        }
        FileUtil::Read(pathname, &rsp.body);
        rsp.set_header("Content-Type", "application/octet-stream"); // 二进制流下载
        rsp.status = 200;
        return;
      }
    private:
      std::string _file_dir;
      httplib::Server _server;
  };
}
