#pragma once
#include <string>
#include <vector>
#include <stack>
#include <map>

class node
{
public:
	int type;
	std::string iden;
	std::string oper;
	double num;
	node() {
		type = 0;
	}
	node(std::string str, int t) {
		if (t == 1) {
			iden = str;
			type = 1;
		}
		else if (t == 2) {
			oper = str;
			type = 2;
		}
	}
	node(double d) {
		node();
		type = 3;
		num = d;
	}
};

class Analyze
{
public:
	#define NUMERROR 1		//�Ƿ��������ƣ����ֿ�ͷ��
	#define FENHAOERROR 2	//���ʽû����;�Ž���
	#define CHARERROR 4		//�Ƿ��ַ�
	#define FUZHIERROR 8	//��ֵ���ŷǷ�
	#define EXPERROR 16		//���ʽ�Ƿ�
	#define OPERATORERROR 32//�������Ƿ�

	static std::map<std::string, double> identable;
	static void identify(std::map<std::string, double>* m);
	static double findIdenValue(std::string str);

	Analyze();
	
	int inspectStr(std::string s);
	node* calculate();
	void clear();

private:
	std::string str;
	std::vector<node*> nodeArray;
	std::map<std::string, int> priority;
	char special[11];
	std::string Operator[13];

	void string_replace(std::string&s1, const std::string&s2, const std::string&s3);
	int split();
	int inspectEqual();
	int inspect(int re);
	int compare(std::string str1, std::string str2);
	node* deal(node* op, node* op1, node* op2);

	bool isSpecial(char ch);
	bool isNum(char ch);
	bool isChar(char ch);
	bool isSubOperator(std::string str);
	bool isOperator(std::string str);
	bool isInspectSuccess;
};