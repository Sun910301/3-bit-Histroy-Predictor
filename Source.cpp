#include<iostream>
#include<string>
#include <math.h>
using namespace::std;
string vector[5] = {"0x0004 addi R4,R0,0","0x0008 addi R3,R0,16","0x000C beq R4,R3,EndLoopI","0x0010 addi R4,R4,1","0x0014 beq R0,R0,LoopI" };
string state_type[8] = { "000","001","010","011","100","101","110","111" };
string state[9] = { "000","SN","SN","SN","SN","SN","SN","SN","SN"};
string input[14] = { "N","N","N","N","T","N","N","T","N","N","T","N","N","T"};
int sum = 0;
int present(int a) {
	if (sum <= 4) {
		cout << vector[a%5];
	}
	else if(sum>4){
		cout << vector[(a+2)%5];
	}
	sum++;
	return 0;
}
/*int makelog(int entry) {
	return log(entry) / log(2);
}*/
int yesorno(string b, string a) {
	string c;

	if (a == "SN" || a == "WN")
		c = "N";
	else if (a == "ST" || a == "WT")
		c = "T";
	if (c == b) {//都是TORN
		return 0;
	}
	else if (c != b)
		return 1;
}
string change(string a) {
	if (a == "SN" || a == "WN")
		return"N";
	else if (a == "ST" || a == "WT")
		return"T";

}
string* statechange(string a,int i) {
	string* c = new string;
	switch (i) {
	case 0://T
		if (a == "ST") {
			*c = "ST";
		}
		else if (a == "WT") {
			*c = "ST";
		}
		else if (a == "WN") {
			*c = "WT";
		}
		else if (a == "SN") {
			*c = "WN";
		}
		break;
	case 1://N
		if (a == "ST") {
			*c = "WT";
		}
		else if (a == "WT") {
			*c = "WN";
		}
		else if (a == "WN") {
			*c = "SN";
		}
		else if (a == "SN") {
			*c = "SN";
		}
		break;
	default:
		break;
		
	}
	return c;
}
string* statetypechange(string a, int i)
{
	string* c = new string;
	switch (i) {
	case 0://T
		if (a == "000") {
			*c = "001";
		}
		else if (a == "001") {
			*c = "011";
		}
		else if (a == "010") {
			*c= "101";
		}
		else if (a == "011") {
			*c = "111";
		}
		else if (a == "100") {
			*c = "001";
		}
		else if (a == "101") {
			*c = "011";
		}
		else if (a == "110") {
			*c = "101";
		}
		else if (a == "111") {
			*c = "111";
		}
		break;
	case 1://N
		if (a == "000") {
			*c = "000";
		}
		else if (a == "001") {
			*c = "010";
		}
		else if (a == "010") {
			*c = "100";
		}
		else if (a == "011") {
			*c = "110";
		}
		else if (a == "100") {
			*c = "000";
		}
		else if (a == "101") {
			*c = "010";
		}
		else if (a == "110") {
			*c = "100";
		}
		else if (a == "111") {
			*c = "110";
		}
		break;
	default:
		break;
	}
	return c;
}
int detectnumber(string a) {
	if (a == "000") {
		return 1;
	}
	else if(a == "001") {
		return 2;
	}
	else if (a == "010") {
		return 3;
	}
	else if (a == "011") {
		return 4;
	}
	else if (a == "100") {
		return 5;
	}
	else if (a == "101") {
		return 6;
	}
	else if (a == "110") {
		return 7;
	}
	else if (a == "111") {
		return 8;
	}
}
int main() {
	int entry = 0;
	//int logresult = 0;
	int i = 0;
	 string numstate[100][9];
	 int numbermispridiction[100] = { 0 };
	cout << "Please input entry(entry>0):" << endl;
	cin >> entry;
	/*string* c = new string[entry];
	 for (int i = 0; i < entry; i++) {
		c[i] = "SN";
	//	cout << c[i];
	}*/ 
	
	//logresult=makelog(entry);

	 for(int j=0;j<entry;j++){
		 for (int k = 0; k < 9; k++) {
			if(k==0){
			 numstate[j][k] = "000";
			}
			else {
				numstate[j][k] = "SN";
			}
		 }
	 }
	while (i < 14) {
		cout <<"entry: "<<i%entry<<"	";
		present(i);
		cout << endl;	
		cout << "(";
		for (int h = 0; h <=8; h++) {
			if(h==8)
			cout << numstate[i % entry][h];
			else
				cout << numstate[i % entry][h]<<",";
		}
		cout << ")	";
		cout << "tureout: " << input[i] << " pridiction: " << change(numstate[i % entry][detectnumber(numstate[i % entry][0])]);
		if(yesorno(input[i], numstate[i % entry][detectnumber(numstate[i % entry][0])])==1){//missprediction
			
			if (input[i] == "T") {
				string* new1 = statechange(numstate[i % entry][detectnumber(numstate[i % entry][0])], 0);//taken
				numstate[i % entry][detectnumber(numstate[i % entry][0])] = *new1;
				//numstate[i % entry][0] = "001";
				string* new2 = statetypechange(numstate[i % entry][0], 0);
				numstate[i % entry][0] = *new2;
			}
			else if (input[i] == "N") {
				string* new1 = statechange(numstate[i % entry][detectnumber(numstate[i % entry][0])], 1);//not taken
				numstate[i % entry][detectnumber(numstate[i % entry][0])] = *new1;
				string* new2 = statetypechange(numstate[i % entry][0], 1);
				numstate[i % entry][0] = *new2;
			}
			numbermispridiction[i % entry]++;
		}
		else if (yesorno(input[i], numstate[i % entry][detectnumber(numstate[i % entry][0])]) == 0) {//right
			if (input[i] == "T") {
				string* new1 = statechange(numstate[i % entry][detectnumber(numstate[i % entry][0])], 0);//taken
				numstate[i % entry][detectnumber(numstate[i % entry][0])] = *new1;
				string* new2 = statetypechange(numstate[i % entry][0], 0);
				numstate[i % entry][0] = *new2;
			}
			else if (input[i] == "N") {
				string* new1 = statechange(numstate[i % entry][detectnumber(numstate[i % entry][0])], 1);//not taken改SN
				numstate[i % entry][detectnumber(numstate[i % entry][0])] = *new1;
				string* new2 = statetypechange(numstate[i % entry][0], 1);//改000
				numstate[i % entry][0] = *new2;
			}
		}
		cout << " miss: " << numbermispridiction[i % entry] << endl<<endl;
		
		
		
		
		i++;
	}
}