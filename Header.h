#pragma once 
#include <iostream>
#include <string>
#include<fstream>
using namespace std;
class comments {
    string *content;
    string user_name;
public:
    comments(string *con =0, string name = " ") {
        content = con;
        user_name = name;
    }
    void setcontent(string* p) {
        content = p;
    }
    void setusername(string p) {
        user_name = p; 
    }
    ~comments() {
        delete[] content;
    }
};
class post {
    string text;
    string pic_id;
    int likes;
    comments p_comments;
    int comCount;
public:
    post(string txt = " ", string id = " ", int lik = 0, comments com = 0, int count = 0) {
        text = txt;
        pic_id = id;
       // cout <<endl<< getpicid();
        likes = lik;
        p_comments = com;
        comCount = count;
    }
    string getpicid() {
        //cout << pic_id;
        return pic_id;
    }
    string gettxt() {
        //cout << pic_id;
        return text;
    }
    int getcommCount()const {
        return comCount;
    }
    string* loadcomments(string name) {
        ifstream fin(name + pic_id + "comments.txt");
        string* s = new string[50];
        int i = 0;
        comCount = 0;
        if (fin) {
            if (getline(fin, s[i])) {
                comCount++;
                i++;
                while (getline(fin, s[i]))
                {
                    comCount++;
                    i++;

                }
            }
            else
                s[0] = "-1";

            fin.close();
        }
        else
        {
            ofstream fw(name + pic_id + "comments.txt");
            fw.close();
            s[0] = "-1";
        }
        p_comments.setcontent(s);
        p_comments.setusername(name + pic_id);
        return s;
    }
    void addcomment(string txt,string name,string u) {
        ifstream fin(name + pic_id + "comments.txt");
        if (fin) {
            ofstream fw((name + pic_id + "comments.txt"), ios::app);
            fw << u << ": " << txt << endl;
            fw.close();
        }
        
    }
    void addlike() {
        likes++;
    }
    ~post() {
        
    }
};
class User {
public:
    virtual void loadMemory() = 0;
    virtual void addpost(string, string) = 0;

};
class user :public User {
private:
    string userName;
    string password;
    string email;
    string profile_pic;
    string* friend_list;
    post** u_posts;
    int friendCount;
    int postCount;
    bool status;
    int count = 0;
    int count1 = 0;
    int msgcount = 0;
public:
    user(string name = "", string pass = "", string mail = "", string pic = "", int friendCount = 0, int postCount = 0) {
        userName = name;
        password = pass;
        email = mail;
        profile_pic = pic;
        friend_list = new string[friendCount];
        for (int i = 0; i < friendCount; i++) {
            friend_list[i] = "";
        }
        u_posts = new post * [postCount];
        for (int i = 0; i < postCount; i++) {
            u_posts[i] = nullptr;
        }
    }
    string getpostpicId(int i) {
        string a = u_posts[i]->getpicid();
        return a;
    }
    string getposttxt(int i) {
        return u_posts[i]->gettxt();
    }
    string getuserName()const {
        return userName;
    }
    string getpassword()const {
        return password;
    }
    string getemail()const {
        return email;
    }/*
    string* getfrientList()const {
        return friend_list;
    }*/
    post *getPosts(int i)const {
        return u_posts[i];
    }
    int getfriendcount()const {
        return friendCount;
    }
    int getmsgcount()const {
        return msgcount;
    }
    int getpostCount()const {
        return postCount;
    }
    string getFriend(int i) {
        return friend_list[i];
}
    bool checkfriend(string a) {
        for (int i = 0; i < friendCount; i++) {
            if (a == friend_list[i]) {
                return 1;
            }
        }
        return 0;
    }
    void setuserName(string name) {
         userName=name;
    }
    void setPassword(string pass) {
        password = pass;
    }
    void setemail(string e) {
        email = e;
    }
    string* loadmessage(string user2) {
        ifstream fin(userName + user2 + "message.txt");
        ifstream fn(user2 + userName + "message.txt");
        string* s = new string[50];
        int i = 0;
        msgcount = 0;
        if (fin) {
            if (getline(fin, s[i])) {
                i++;
                while (getline(fin, s[i]))
                {
                    msgcount++;
                    // cout << s[i];
                    i++;

                }
            }
            else
                s[0] = "-1";

            fin.close();
        }
        else if (fn) {
            if (getline(fn, s[i])) {
                i++;
                while (getline(fn, s[i]))
                {

               
                    msgcount++;
                    // cout << s[i];
                    i++;
                }
            }
            else
                s[0] = "-1";

            fn.close();
        }
        else
        {
            ofstream fw(userName + user2 + "message.txt");
            fw.close();
            s[0] = "-1";
        }
        return s;
    }
    void loadMemory()override {
        string filname = userName + "posts" + ".txt";
        string filname2 = userName + "postscaption" + ".txt";
        string filname3 = userName + "postcount" + ".txt";
        string filname1 = userName + "likecount" + ".txt";
        string filname4 = userName + "friends" + ".txt";
        ifstream fin(filname);
        ifstream f(filname3);
        ifstream f1(filname1);
        ifstream f2(filname4);
        int num, num1, num2;
        f >> num;//postcount
        f >> num1;//friendcount
        f1 >> num2;
        postCount = num;
        friendCount = num1;
        friend_list = new string[friendCount+1];
        u_posts = new post * [postCount];
        string* arr = new string[postCount + 1];
        string* arr1 = new string[postCount + 1];
        string* arr2 = new string[num1 + 1];
        int i = 0;
        for (i = 0; i < postCount ; i++) {
            getline(fin, arr[i]);
            
        }
        
        ifstream fn(filname2);
        for (i = 0; i < postCount; i++) {
            getline(fn, arr1[i]);
        }
        for (i = 0; i < friendCount; i++) {
            getline(f2, arr2[i]);
        }
         for (i = 0; i<friendCount; i++) {
            friend_list[i] = arr2[i];
        }
        f >> num; int j = 1;
        for (int i = 0; i < postCount; i++) {
            u_posts[i] = new post(arr1[i], arr[i], num2);
          
            j++;
        }
        fn.close();
        fin.close(); f.close(); f1.close(); f2.close();
    }
    void addpost(string txt, string id) {
        postCount++;
        post** temp = new post * [postCount + 1];
        string filname = userName + "posts" + ".txt";
        string filname2 = userName + "postscaption" + ".txt";
        string filname3 = userName + "postcount" + ".txt";
        ofstream fiw(filname, ios::app);
        ifstream f1(filname3);
        
        fiw << id ;
        fiw.close();
        int num, num1;
        f1 >> num;//postcount
        f1 >> num1;//friendcount
        ofstream f(filname3);
        num++;
        f << num << endl << num1;
        f.close();
        ofstream fw(filname2, ios::app);
        fw << txt;
        fw.close();
        loadMemory();
    }
    void sendmessage(string name, string txt) {
        ifstream fin(userName + name + "message.txt");
        ifstream fn( name +userName+ "message.txt");
        if (fin) {
            ofstream fw(userName + name + "message.txt", ios::app);
            fw << userName << ": " << txt << endl;
            fw.close();
        }
        else if (fn) {
            ofstream fw(name + userName + + "message.txt",ios::app);
            fw << userName << ": " << txt << endl;
            fw.close();
        }
    }
    string * loadcomments(int i) {
        return u_posts[i]->loadcomments(userName);
    }
    int getcommCount(int i) {
        return u_posts[i]->getcommCount();
    }
    void addcomment(string txt,int i,string u) {
        u_posts[i]->addcomment(txt, userName,u);
    }
    ~user() {
        delete[] friend_list;
        for (int i = 0; i < postCount; i++) {
            delete u_posts[i];
        }
        delete[] u_posts;
    }
};
