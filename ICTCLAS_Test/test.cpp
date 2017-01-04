/******************************************************************************* 
Filename   : TEST.cpp
Version    : ver 1.0
Author     : MingZz
Date       : 2014/03/22  
Description: ���ݴ���ͳ����ش��Ե�Ƶ��
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
	AppendtoFile("Test.log", msg);
}

void doFilename(const string sSrcFilename)
{
	string sDsnFilename = ReplaceStr(sSrcFilename,sSrcDirectory,sDsnDirectory);
	My_Log("sDsnFilename" + sSrcFilename);
	My_Log("sDsnFilename" + sDsnFilename);

}

//������ȣ������ļ����������ļ� �������ļ���
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
{	//argv[0] ָ��exe�ļ���
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
	

	My_Log("success...!!!");
	
	return 0;
}

