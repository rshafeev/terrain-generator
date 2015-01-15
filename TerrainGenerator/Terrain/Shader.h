#pragma once
#include "afx.h"

#include "GLlib.h"
class CShader
{
 char* textFileRead(char *fn);                                //������ ����  fn � ���������� ����������� ������
 int   textFileWrite(char *fn, char *s);                      //���������� � ���� fn ������ s
 void  setShaders(char * fileV,char *fileF);                  //�������, �������� ��������� ��������� 
 GLuint v,f,ShadPtr;
 bool  createdFlag;                                           //���� �� ������� ���������?
public:
	void    LoadShader(CString VertFName,CString FragFName);  //�������� �������
	GLuint  GetShadPt();                                      //�������� ���������� ������� �������
	void    Use();                                            //������������ ������
	void    Close();                                          //������� ����������� ������
    void    DestroyProgram();                                 //������� ���������
	bool    IsCreated();                                      //���������� createdFlag
	bool    SetUniformFloat(const char* name, float value);   //�������  ���������� ������� name ��������  value
	bool    SetUniformInt  (const char* name, int value);     //�������  ���������� ������� name ��������  value
	bool    SetUniformVec2 (const char* name,float value1,float value2);
	CShader(void);
	~CShader(void);
};
//=========================================================================================================================

