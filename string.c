#include<iostream>
#include<string.h>
using namespace std;;

class my_string
{
	public:
		char *p;
		
  ~my_string(){
			if(p){
				delete []p;
				p=0;
			}
		}

		my_string(){//def constructor
			p=0;
		}

		my_string(const char *s){//parameterised constructor
			if(s){
				int l=strlen(s);
				p=new char[l+1];
				strcpy(p,s);
			}
			else
				p=0;
		}

		my_string(const my_string &s){//copy constructor
			if(s.p!=0){
				int l=strlen(s.p);
				p=new char[l+1];
				strcpy(p,s.p);
			}
			else{
				p=0;
			}
		}

		my_string& operator =(const my_string &s);
		my_string operator +(const my_string &s);
		bool operator ==(const my_string& s);
		int length();
};

my_string& my_string::operator =(const my_string &s){//assignment operator overload
	if(this!=&s){
		if(s.p!=0){
			int l=strlen(s.p);
			if(p){
				delete []p;
			}
			p=new char[l+1];
			strcpy(p,s.p);
		}
		else{
			p=0;
		}
	}
	return *this;
}

my_string my_string::operator +(const my_string &s){
	int l1=0,l2=0,l=0;
	char *data=0;
	my_string o;

	if(s.p!=0){//source contain valid data size
		l2=strlen(s.p);
	}

	if(p!=0){//desi contain valid data size
		l1=strlen(p);
	}

	l=l1+l2+1;//total size

	if(l>0){
		data=new char[l];// m/r allocate 
		if(l1>0){// source contain any data
			strcpy(data,p);// move data to new m/r
		}
		if(l2>0){// desti valid data
			strcat(data,s.p); // move at end of new m/r
		}
		o.p=data;
	}
	else{
		o.p=0;
	}
	return o;
}

bool my_string::operator ==(const my_string& s){
	int r=0;

	if(p && s.p){//contain any string data
		return strcmp(p,s.p) == 0;
	}
	else
		return false;
}

int my_string::length(){
	if(p){
		return strlen(p);
	}
	else
		return 0;
}

ostream & operator <<(ostream &out,const my_string &s){
	if(s.p){//valid
		out<<s.p;
	}
	return out;
}

istream & operator >>(istream& in,my_string &s){
	int capacity=16;
	int len=0;
	char ch=0;
	char *t=0,*d=0;
  
	if(s.p){
		delete []s.p;
		s.p=0;
	}
  
	//skip leading space/new_line/tabs
	//read upto space/new_line/EOF_reached
	if(in>>ch){//skip leading 
		do{
			if(ch!=' ' && ch!='\n'){
				if(len==0 || len==capacity-1){
					if(len==0)
						d=new char[capacity];
					else{
						t=d;
						capacity *=2;
						d=new char[capacity];
						strcpy(d,t);
						delete []t;
					}
				}
				d[len]=ch;
				len++;
			}
			else
				break;
		}while(in.get(ch));
		if(d){
			d[len]=0;
			s.p=d;
		}
	}
	return in;
}


istream& getline(istream &in,my_string &s){
	int len=0;
	char *t=0,*d=0,ch=0;
	int capacity=16;
  
	if(s.p){
		delete []s.p;
		s.p=0;
	}

	//read upto new_line/EOF_reached
	while(in.get(ch)){
		if(ch!='\n'){
			if(len==0 || len==capacity-1){
				if(len==0)
					d=new char[capacity];
				else{
					t=d;
					capacity *=2;
					d=new char[capacity];
					strcpy(d,t);
					delete []t;
				}
			}
			d[len]=ch;
			len++;
		}
		else
			break;
	}
	if(d){
		d[len]=0;
		s.p=d;
	}
	return in;
}


int main()
{
	my_string s1;
  my_string s2("hi");
  my_string s3(s2);

  cin>>s1;
  getline(cin,s2);
  
  cout<<s1<<endl;
  cout<<s2<<endl;
  cout<<s3<<endl;
}

