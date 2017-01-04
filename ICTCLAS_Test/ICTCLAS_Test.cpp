/******************************************************************************* 
Filename   : ICTCLAS_TEST.cpp
Version    : ver 1.0
Author     : MingZz
Date       : 2014/03/22  
Description: ����ICTCLAS��API����һ��Ŀ¼�е��ļ���������Ŀ¼�е��ļ��� ���зִʣ� �ִʽ�����浽����һ��Ŀ¼�У���������Ӧ�ļ�������
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include<io.h>

#include "ICTCLAS50.h"
#pragma comment(lib, "ICTCLAS50.lib") //ICTCLAS50.lib����뵽������

using namespace std;


#define SUCCESS		1
#define ERROR		0

eCodeType eCt =  CODE_TYPE_GB;	// �ļ��������ͣ�Ĭ��Ϊ  CODE_TYPE_GB
bool bPOStagged = 1;			// �Ƿ���ҪPOS���
int nPOSmap = ICT_POS_MAP_FIRST;// ���Ա�ע������
string sSrcDirectory = "";	// Դ�ļ�Ŀ¼
string sDsnDirectory = "";	// Ŀ���ļ�Ŀ¼

/**
��������AppendtoFile
����1��	Ҫ�򿪵��ļ���
����2��	Ҫ׷�ӵ�����
���ã�	��ָ���ļ���׷�����ݣ�����ļ������ڣ��򴴽�
**/
bool AppendtoFile(const string filename, const string content)
{
	ofstream ofcout;//�����������һ������
	ofcout.open(filename, ios::app);//����ļ�����
	if(!ofcout){
		// �ļ�������,�򴴽�
		ofstream ofcout(filename);
	}
	ofcout << content;
	ofcout.close();
	return SUCCESS;
}
/**
	�ַ����滻
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
��������My_Log
����1��	��־��Ϣ
���ã�	�����־��Ϣ��������־��Ϣ��¼����־�ļ�
**/
void My_Log(const string message)
{
	string msg = message + "\n";
	cout << msg << endl;
	// ���浽Log�ļ�
	AppendtoFile("ICTCLAS_Test.log", msg);
}
/**
��������My_ICTCLAS_Init
���ã�	��ʼ��ICTCLAS,�������־
**/
bool My_ICTCLAS_Init()
{
	if(!ICTCLAS_Init()) //��ʼ���ִ������
	{
		My_Log("Init fails...");  
		return ERROR;
	}
	My_Log("Init ok...");
	return SUCCESS;
}

//�����ļ����������ļ� �������ļ���
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
        //�ж��Ƿ�����Ŀ¼
        if (FileInfo.attrib & _A_SUBDIR)    
        {
            //���������Ҫ
            if( (strcmp(FileInfo.name,".") != 0 ) &&(strcmp(FileInfo.name,"..") != 0))   
            {
                string newPath = folderPath + "\\" + FileInfo.name;
				// ����Ŀ¼�ṹ
				string sDsnfolderPath = ReplaceStr(newPath,sSrcDirectory,sDsnDirectory);
				// ��DOS���������� Ŀ¼
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
			// ���ļ��ִ�
			if(!ICTCLAS_FileProcess(sSrcFilename.c_str(),sDsnFilename.c_str(),eCt,bPOStagged))
			{// �˴�API��Bug  ֻ�����Ѵ��ڵ�Ŀ¼���½��ļ����������ڲ����ڵ�Ŀ¼���½��ļ���Ҫ�ô˴�API��Ҫ����Ŀ��Ŀ¼�½�����ͬ�ṹĿ¼
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
��������My_ICTCLAS_DirectoryProcess
����1��	Դ�ļ�·��
����2��	Ŀ���ļ�·��
���ã�	��Դ�ļ�·���µ��ļ����зִʣ����ѽ��������Ŀ��·����
**/
bool My_ICTCLAS_DirectoryProcess()
{// ����Դ�ļ�·�� ��ȡԴ�ļ��� ��ȡĿ���ļ��� �ִ� 
	My_Log("direc process...");
	string DosCmd = "mkdir " + sDsnDirectory;
	My_Log("DosCmd:"+DosCmd);
	int status = system(DosCmd.c_str());// ���ȴ���Ŀ��Ŀ¼��Ŀ¼
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
	// �˴�API��Bug  ֻ�����Ѵ��ڵ�Ŀ¼���½��ļ����������ڲ����ڵ�Ŀ¼���½��ļ���Ҫ�ô˴�API��Ҫ����Ŀ��Ŀ¼�½�����ͬ�ṹĿ¼

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
{	//argv[0] ָ��exe�ļ���
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
			throw string("����Ĳ�������ȷ!");
			return ERROR;
		}
		if(!Init(argv)){
			My_Log("!Init");
			throw string("Init����ȷ!");
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

