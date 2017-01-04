/******************************************************************************* 
Filename   : TEST.cpp
Version    : ver 1.0
Author     : MingZz
Date       : 2014/03/22  
Description: 根据词性统计相关词性的频率
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <regex>
#include <boost/regex.hpp>


using namespace std;


#define SUCCESS		1
#define ERROR		0


string sSrcDirectory = "";	// 源文件目录
string sDsnDirectory = "";	// 目标文件目录

/**
函数名：AppendtoFile
参数1：	要打开的文件名
参数2：	要追加的内容
作用：	在指定文件中追加内容，如果文件不存在，则创建
**/
bool AppendtoFile(const string filename, const string content)
{
	ofstream ofcout;//定义输出流的一个对象
	ofcout.open(filename, ios::app);//添加文件内容
	if(!ofcout){
		// 文件不存在,则创建
		ofstream ofcout(filename);
	}
	ofcout << content;
	ofcout.close();
	return SUCCESS;
}
/**
	字符串替换
**/
string ReplaceStr(const string sSrc,const string sMatchStr,const string sReplaceStr)
{
	string str = sSrc;
	string::size_type pos=0;
	string::size_type a=sMatchStr.size();
	string::size_type b=sReplaceStr.size();
	while((pos=str.find_first_of(sMatchStr))!=string::npos)
	{
		str.replace(pos,a,sReplaceStr);
		pos+=b;
		break;
	}
	
	return str;
}
	 

/**
函数名：My_Log
参数1：	日志消息
作用：	输出日志消息，并将日志消息记录到日志文件
**/
void My_Log(const string message)
{
	string msg = message + "\n";
	cout << msg << endl;
	// 保存到Log文件
	AppendtoFile("Test.log", msg);
}

void doFilename(const string sSrcFilename)
{
	string sDsnFilename = ReplaceStr(sSrcFilename,sSrcDirectory,sDsnDirectory);
	My_Log("sDsnFilename" + sSrcFilename);
	My_Log("sDsnFilename" + sDsnFilename);

}

//深度优先，遍历文件夹下所有文件 包括子文件夹
void dfsFolder(const string folderPath, ofstream &fout)
{
	My_Log("dfsFolder...");
	My_Log(folderPath);
    _finddata_t FileInfo;
    string strfind = folderPath + "\\*";
    long Handle = _findfirst(strfind.c_str(), &FileInfo);
    
    if (Handle == -1L)
    {
        cerr << "can not match the folder path" << endl;
        exit(-1);
    }
    do{
		My_Log("do...");
        //判断是否有子目录
        if (FileInfo.attrib & _A_SUBDIR)    
        {
            //这个语句很重要
            if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
            {
                string newPath = folderPath + "\\" + FileInfo.name;
				// 创建目录结构
				string sDsnfolderPath = ReplaceStr(newPath,sSrcDirectory,sDsnDirectory);
				// 用DOS命令来创建 目录
				string DosCmd = "mkdir " + sDsnfolderPath;
				My_Log("DosCmd: " + DosCmd);
				system(DosCmd.c_str());

                dfsFolder(newPath, fout);
            }
        }
        else  
        {
			

			string sSrcFilename = folderPath + "\\" + FileInfo.name;

			doFilename(sSrcFilename);
			
			
        }
    }while (_findnext(Handle, &FileInfo) == 0);

    _findclose(Handle);
    fout.close();
}









bool My_Help()
{
	cout << "My_Help...";
	return SUCCESS;
}

bool Init(const char **argv)
{	//argv[0] 指向exe文件名
	sSrcDirectory = argv[1];
	sDsnDirectory = argv[2];
	
	
	
	return SUCCESS;
}

int main(int argc, char *argv[])
{
	try{
		if(argc != 5){
			My_Help();
			My_Log("argc != 5");
			throw string("传入的参数不正确!");
			return ERROR;
		}
		if(!Init(argv)){
			My_Log("!Init");
			throw string("Init不正确!");
			My_Help();
			return ERROR;
		}
	}catch(string e){
		cout << e << endl;
		return -1;
	}
	

	My_Log("success...!!!");
	
	return 0;
}

