#include <iostream>
#include <string>
#include <cmath>
#include<cstdlib>
#include <time.h>
using namespace std;

//������ת��Ϊʮ������
string twoTOsixteen(string str) {
	string hex = "";
	int temp = 0;
	while (str.size() % 4 != 0) {
		str = "0" + str;
	}
	int tmp = str.size();
	for (int i = 0; i < tmp; i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;
		if (temp < 10) {
			hex += to_string(temp);
		}
		else {
			hex += 'A' + (temp - 10);
		}
	}
	return hex;
}

//ʮ������ת��Ϊ������
//�����㷨��ʹ����һ�������������Σ�һ��Ϊ�����ַ�ת����һ��Ϊ����ת��
//��ˣ���Բ�ͬ���������ͬ���Ż���ͨ�������жϣ�����������ת�����ԣ�ʹ��ѭ��չ����4���ķ����Ż�
//����֮�����ѭ������Ҫ����ĳ�������ǰʹ�ñ����洢������ѭ���еļ�����

string sixteenTOtwo(string str) {
	string bin = "";
	string table[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	int tmp = str.size();
	if (tmp % 4 == 0)
	{
		for (int i = 0; i < tmp; i+=4) {
			if (str[i] >= 'A' && str[i] <= 'F') {
				bin += table[str[i] - 'A' + 10];
			}
			else {
				bin += table[str[i] - '0'];
			}
			if (str[i+1] >= 'A' && str[i+1] <= 'F') {
				bin += table[str[i+1] - 'A' + 10];
			}
			else {
				bin += table[str[i+1] - '0'];
			}
			if (str[i+2] >= 'A' && str[i+2] <= 'F') {
				bin += table[str[i+2] - 'A' + 10];
			}
			else {
				bin += table[str[i+2] - '0'];
			}
			if (str[i+3] >= 'A' && str[i+3] <= 'F') {
				bin += table[str[i+3] - 'A' + 10];
			}
			else {
				bin += table[str[i+3] - '0'];
			}
		}
	}
	else
	{
		for (int i = 0; i < tmp; i++) {
			if (str[i] >= 'A' && str[i] <= 'F') {
				bin += table[str[i] - 'A' + 10];
			}
			else {
				bin += table[str[i] - '0'];
			}
		}
	}
	
	return bin;
}

//ʮ������ת��Ϊʮ���ƣ������ַ���
int sixteenTOten(char str) {
	int dec = 0;
	if (str >= 'A' && str <= 'F') {
		dec += (str - 'A' + 10);
	}
	else {
		dec += (str - '0');
	}
	return dec;
}

//ѭ������
string lshift(string str, int len) {
	string res = sixteenTOtwo(str);
	res = res.substr(len) + res.substr(0, len);
	return twoTOsixteen(res);
}

//���
//���ڴ�������ö�Ϊ�����ַ����ã�����û�н���ѭ��չ���Ż�
//���򣬷��������˶�����ж���䣬���Ӷ��������

string yihuo(string str1, string str2) {
	string res1 = sixteenTOtwo(str1);
	string res2 = sixteenTOtwo(str2);
	string res = "";
	int tmp = res1.size();
	for (int i = 0; i < tmp; i++) {
		if (res1[i] == res2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return twoTOsixteen(res);
}

//�Ż���ѭ��չ����ȫ����+�����������㣨���ټ��㿪����
string feiline(string str) {//�����Ա任t����ʵ��
	string Sbox[16][16] = { {"D6","90","E9","FE","CC","E1","3D","B7","16","B6","14","C2","28","FB","2C","05"},
						 {"2B","67","9A","76","2A","BE","04","C3","AA","44","13","26","49","86","06","99"},
						 {"9C","42","50","F4","91","EF","98","7A","33","54","0B","43","ED","CF","AC","62"},
						 {"E4","B3","1C","A9","C9","08","E8","95","80","DF","94","FA","75","8F","3F","A6"},
						 {"47","07","A7","FC","F3","73","17","BA","83","59","3C","19","E6","85","4F","A8"},
						 {"68","6B","81","B2","71","64","DA","8B","F8","EB","0F","4B","70","56","9D","35"},
						 {"1E","24","0E","5E","63","58","D1","A2","25","22","7C","3B","01","21","78","87"},
						 {"D4","00","46","57","9F","D3","27","52","4C","36","02","E7","A0","C4","C8","9E"},
						 {"EA","BF","8A","D2","40","C7","38","B5","A3","F7","F2","CE","F9","61","15","A1"},
						 {"E0","AE","5D","A4","9B","34","1A","55","AD","93","32","30","F5","8C","B1","E3"},
						 {"1D","F6","E2","2E","82","66","CA","60","C0","29","23","AB","0D","53","4E","6F"},
						 {"D5","DB","37","45","DE","FD","8E","2F","03","FF","6A","72","6D","6C","5B","51"},
						 {"8D","1B","AF","92","BB","DD","BC","7F","11","D9","5C","41","1F","10","5A","D8"},
						 {"0A","C1","31","88","A5","CD","7B","BD","2D","74","D0","12","B8","E5","B4","B0"},
						 {"89","69","97","4A","0C","96","77","7E","65","B9","F1","09","C5","6E","C6","84"},
						 {"18","F0","7D","EC","3A","DC","4D","20","79","EE","5F","3E","D7","CB","39","48"} };
	string res = "";
	//�Ż�����ʹ��ѭ��������ѭ���Ĵ����٣�ֻ��4�Σ�����ֱ�Ӷ����е�ѭ��ѭ��չ��������ѭ���жϵĿ���
	//�Ż������ڶ����е�ѭ��������ѭ��չ�������������ļ��㣬�����ֶ���ǰ��ɣ���������ʱ�ļ�����
	res += Sbox[sixteenTOten(str[0])][sixteenTOten(str[1])];
	res += Sbox[sixteenTOten(str[2])][sixteenTOten(str[3])];
	res += Sbox[sixteenTOten(str[4])][sixteenTOten(str[5])];
	res += Sbox[sixteenTOten(str[6])][sixteenTOten(str[7])];
	
	return res;
}

string L(string str) {//���Ա任L����ʵ��
	return yihuo(yihuo(yihuo(yihuo(str, lshift(str, 2)), lshift(str, 10)), lshift(str, 18)), lshift(str, 24));
}

string L2(string str) {//���Ա任L'����ʵ��
	return yihuo(yihuo(str, lshift(str, 13)), lshift(str, 23));
}

string T(string str) {//���ڼӽ����㷨�еĺϳ��û�T����ʵ��
	return L(feiline(str));
}

string T2(string str) {//������Կ��չ�㷨�еĺϳ��û�T����ʵ��
	return L2(feiline(str));
}

//�Ż���ѭ��չ����4��
string keyex(string MK) {//��Կ��չ����ʵ��
	string FK[4] = { "A3B1BAC6", "56AA3350", "677D9197", "B27022DC" };
	string CK[32] = { "00070E15", "1C232A31", "383F464D", "545B6269",
					  "70777E85", "8C939AA1", "A8AFB6BD", "C4CBD2D9",
					  "E0E7EEF5", "FC030A11", "181F262D", "343B4249",
					  "50575E65", "6C737A81", "888F969D", "A4ABB2B9",
					  "C0C7CED5", "DCE3EAF1", "F8FF060D", "141B2229",
					  "30373E45", "4C535A61", "686F767D", "848B9299",
					  "A0A7AEB5", "BCC3CAD1", "D8DFE6ED", "F4FB0209",
					  "10171E25", "2C333A41", "484F565D", "646B7279" };
	string K[36] = { yihuo(MK.substr(0,8),FK[0]),yihuo(MK.substr(8,8),FK[1]),yihuo(MK.substr(16,8),FK[2]),yihuo(MK.substr(24),FK[3]) };
	string rks = "";
	//�Ż���ѭ��չ����4��
	for (int i = 0; i < 32; i+=4) {
		K[i + 4] = yihuo(K[i], T2(yihuo(yihuo(yihuo(K[i + 1], K[i + 2]), K[i + 3]), CK[i])));
		rks += K[i + 4];

		K[i + 5] = yihuo(K[i+1], T2(yihuo(yihuo(yihuo(K[i + 2], K[i + 3]), K[i + 4]), CK[i+1])));
		rks += K[i + 5];

		K[i + 6] = yihuo(K[i+2], T2(yihuo(yihuo(yihuo(K[i + 3], K[i + 4]), K[i + 5]), CK[i+2])));
		rks += K[i + 6];

		K[i + 7] = yihuo(K[i+3], T2(yihuo(yihuo(yihuo(K[i + 4], K[i + 5]), K[i + 6]), CK[i+3])));
		rks += K[i + 7];
	}
	return rks;
}

//�Ż���ѭ��չ����4��
string jia(string plain, string key) {//���ܺ���ʵ��
	
	string cipher[36] = { plain.substr(0,8),plain.substr(8,8),plain.substr(16,8),plain.substr(24) };
	string rks = keyex(key);
	//�Ż���ѭ��չ����4��
	for (int i = 0; i < 32; i+=4) {
		cipher[i + 4] = yihuo(cipher[i], T(yihuo(yihuo(yihuo(cipher[i + 1], cipher[i + 2]), cipher[i + 3]), rks.substr(8 * i, 8))));
		cipher[i + 5] = yihuo(cipher[i+1], T(yihuo(yihuo(yihuo(cipher[i + 2], cipher[i + 3]), cipher[i + 4]), rks.substr(8 * (i+1), 8))));
		cipher[i + 6] = yihuo(cipher[i+2], T(yihuo(yihuo(yihuo(cipher[i + 3], cipher[i + 4]), cipher[i + 5]), rks.substr(8 * (i+2), 8))));
		cipher[i + 7] = yihuo(cipher[i+3], T(yihuo(yihuo(yihuo(cipher[i + 4], cipher[i + 5]), cipher[i + 6]), rks.substr(8 * (i+3), 8))));
	}
	return cipher[35] + cipher[34] + cipher[33] + cipher[32];
}

//�Ż���ѭ��չ����4��
string jie(string cipher, string key) {//���ܺ���ʵ��
	string plain[36] = { cipher.substr(0,8),cipher.substr(8,8), cipher.substr(16,8), cipher.substr(24,8) };
	string rks = keyex(key);
	//�Ż���ѭ��չ����4��
	for (int i = 0; i < 32; i+=4) {
		plain[i + 4] = yihuo(plain[i], T(yihuo(yihuo(yihuo(plain[i + 1], plain[i + 2]), plain[i + 3]), rks.substr(8 * (31 - i), 8))));
		plain[i + 5] = yihuo(plain[i+1], T(yihuo(yihuo(yihuo(plain[i + 2], plain[i + 3]), plain[i + 4]), rks.substr(8 * (30 - i), 8))));
		plain[i + 6] = yihuo(plain[i+2], T(yihuo(yihuo(yihuo(plain[i + 3], plain[i + 4]), plain[i + 5]), rks.substr(8 * (29 - i), 8))));
		plain[i + 7] = yihuo(plain[i+3], T(yihuo(yihuo(yihuo(plain[i + 4], plain[i + 5]), plain[i + 6]), rks.substr(8 * (28 - i), 8))));
	}
	return plain[35] + plain[34] + plain[33] + plain[32];
}



int main() {//������
	
	string plain = "8471890BAD9235717CEEDA249FFEBBAC";
	string key = "FFABDDC3384187DCCB291840ABCDAAE8";
	long beginTime = clock();
	string cipher = jia(plain, key);
	string plain1 = jie(cipher, key);
	long endTime = clock();
	std::cout << "endTime-beginTime:" << ((double)(endTime - beginTime)) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	cout << "����Ϊ��" << plain << endl;
	cout << "��ԿΪ��" << key << endl;
	cout << "���ܺ������Ϊ��" << cipher << endl;
	cout << "����������ʹ��ͬ����Կ���ܺ������Ϊ��" << plain1 << endl;
	system("pause");
	return 0;
	
	
}
