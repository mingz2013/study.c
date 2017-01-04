/******************************************************************************* 
Filename   : ICTCLAS_TEST.cpp
Version    : ver 1.0
Author     : MingZz
Date       : 2014/03/22  
Description: 调用ICTCLAS的API，将一个目录中的文件（包括子目录中的文件） 进行分词， 分词结果保存到另外一个目录中，并按照相应文件名命名
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include<io.h>

#include "ICTCLAS50.h"
#pragma comment(lib, "ICTCLAS50.lib") //ICTCLAS50.lib库加入到工程中

using namespace std;


#define SUCCESS		1
#define ERROR		0

eCodeType eCt =  CODE_TYPE_GB;	// 文件编码类型，默认为  CODE_TYPE_GB
bool bPOStagged = 1;			// 是否需要POS标记
int nPOSmap = ICT_POS_MAP_FIRST;// 词性标注集类型
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
	AppendtoFile("ICTCLAS_Test.log", msg);
}
/**
函数名：My_ICTCLAS_Init
作用：	初始化ICTCLAS,并输出日志
**/
bool My_ICTCLAS_Init()
{
	if(!ICTCLAS_Init()) //初始化分词组件。
	{
		My_Log("Init fails...");  
		return ERROR;
	}
	My_Log("Init ok...");
	return SUCCESS;
}

//遍历文件夹下所有文件 包括子文件夹
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
			string sDsnFilename = ReplaceStr(sSrcFilename,sSrcDirectory,sDsnDirectory);
			My_Log("sDsnFilename" + sSrcFilename);
			My_Log("sDsnFilename" + sDsnFilename);
			// 对文件分词
			if(!ICTCLAS_FileProcess(sSrcFilename.c_str(),sDsnFilename.c_str(),eCt,bPOStagged))
			{// 此处API有Bug  只能在已存在的目录下新建文件，而不能在不存在的目录下新建文件，要用此处API，要先在目标目录下建立相同结构目录
				My_Log("ICTCLAS_FileProcess is return false when filename is  " + sSrcFilename);
				continue;
			}
           // fout << folderPath << "\\" << FileInfo.name  << " ";
			
        }
    }while (_findnext(Handle, &FileInfo) == 0);

    _findclose(Handle);
    fout.close();
}


/**
函数名：My_ICTCLAS_DirectoryProcess
参数1：	源文件路径
参数2：	目标文件路径
作用：	将源文件路径下的文件进行分词，并把结果保存在目标路径下
**/
bool My_ICTCLAS_DirectoryProcess()
{// 遍历源文件路径 获取源文件名 获取目标文件名 分词 
	My_Log("direc process...");
	string DosCmd = "mkdir " + sDsnDirectory;
	My_Log("DosCmd:"+DosCmd);
	int status = system(DosCmd.c_str());// 首先创建目标目录根目录
	My_Log("status:" + status);
	ofstream fout;
	dfsFolder(sSrcDirectory, fout);

	

	return SUCCESS;
}


bool Start_ICTCLAS()
{
	My_Log("Start ictclas...1");
	if(!My_ICTCLAS_Init()) return ERROR;
	My_Log("Start ictclas...2");
	if(!ICTCLAS_SetPOSmap(nPOSmap))return ERROR;
	My_Log("Start ictclas...3");
	if(!My_ICTCLAS_DirectoryProcess()) return ERROR;
	//ICTCLAS_FileProcess("d:\\001\\aaa.txt","d:\\002\\aaaxxx.txt", CODE_TYPE_GB,1);
	// 此处API有Bug  只能在已存在的目录下新建文件，而不能在不存在的目录下新建文件，要用此处API，要先在目标目录下建立相同结构目录

	My_Log("Start ictclas...4");
	if(!ICTCLAS_Exit())return ERROR;
	My_Log("Start ictclas...5");

	return SUCCESS;
}

bool My_Help()
{
	cout << "My_Help...";
	return SUCCESS;
}

bool Init(char **argv)
{	//argv[0] 指向exe文件名
	sSrcDirectory = argv[1];
	sDsnDirectory = argv[2];
	
	if(strcmp(argv[3], "CODE_TYPE_UNKNOWN") == 0) eCt = CODE_TYPE_UNKNOWN;
	else if(strcmp(argv[3], "CODE_TYPE_ASCII") == 0) eCt = CODE_TYPE_ASCII;
	else if(strcmp(argv[3], "CODE_TYPE_GB") == 0) eCt = CODE_TYPE_GB;
	else if(strcmp(argv[3], "CODE_TYPE_UTF8") == 0) eCt = CODE_TYPE_UTF8;
	else if(strcmp(argv[3], "CODE_TYPE_BIG5") == 0) eCt = CODE_TYPE_BIG5;
	else return ERROR;
	
	if(strcmp(argv[4], "ICT_POS_MAP_SECOND") == 0) nPOSmap = ICT_POS_MAP_SECOND;
	else if(strcmp(argv[4], "ICT_POS_MAP_FIRST") == 0) nPOSmap = ICT_POS_MAP_FIRST;
	else if(strcmp(argv[4], "PKU_POS_MAP_SECOND") == 0) nPOSmap = PKU_POS_MAP_SECOND;
	else if(strcmp(argv[4], "PKU_POS_MAP_FIRST") == 0) nPOSmap = PKU_POS_MAP_FIRST;
	else return ERROR;
	
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
	
	if(!Start_ICTCLAS()){
		My_Log("!Start_ICTCLAS error..");
		return ERROR;
	}

	My_Log("success...!!!");
	
	return 0;
}

