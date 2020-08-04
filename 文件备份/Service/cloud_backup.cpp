#include "cloud_backup.hpp"
#include <thread>


/*
void test_Compress(char* argv[]){
  // agrv[1] -- 源文件名称
  // agrv[2] -- 压缩包名称
  _cloud_sys::CompressUtil::Compress(argv[1], argv[2]);
  std::string file(argv[2]);
  file.append(".txt");
  _cloud_sys::CompressUtil::UnCompress(argv[2], file);
}
*/

/*
void DataManager_test(int argc, char* argv[]){
  _cloud_sys::DataManage data_manage("./test.txt");
  
    测试数据管理模块:插入<源文件名称, 压缩包名称>,持久化存储
  data_manager.Insert("a.txt", "a.txt.gz");
  data_manager.Insert("b.txt", "b.txt");
  data_manager.Insert("c.txt", "c.txt.gz");
  data_manager.Insert("d.txt", "d.txt");
  data_manager.Storage();


  data_manage.InitLoad();
  data_manage.Insert("b.txt", "b.txt.gz");
  std::vector<std::string> list;
  data_manage.GetAllFileName(&list);
  std::cout << "获取所有源文件信息---测试\n";
  for(auto it : list){
    std::cout << it << "\n";
  }
  list.clear();
  data_manage.NonCompressList(&list);
  std::cout << "获取未压缩文件信息---测试\n";
  for(auto it : list){
    std::cout << it << "\n";
  }
}
*/
void test_non_compress(){
  _cloud_sys::NonHotCompresss no_hotFile(GZFILE_DIR, BACKUP_DIR);
  no_hotFile.Start();
  return;
}

void thr_http_server(){
  _cloud_sys::Server srv;
  srv.Start();
  return;
}

int main(int argc, char* argv[]){
  // 文件备份路径不存在则创建
  if(boost::filesystem::exists(GZFILE_DIR) == false){
    boost::filesystem::create_directory(GZFILE_DIR);
  }
  // 压缩包存放路径不存在则创建
  if(boost::filesystem::exists(BACKUP_DIR) == false){
    boost::filesystem::create_directory(BACKUP_DIR);
  }
  std::thread thr_compress(test_non_compress);
  std::thread thr_server(thr_http_server);
  thr_server.join();
  thr_server.join();

  return 0;
}
