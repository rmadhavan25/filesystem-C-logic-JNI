//============================================================================
// Name        : nativeGetFiles.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "../header/controllers_GetFiles.h"
#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;


jstring JNICALL Java_controllers_GetFiles_getFiles
  (JNIEnv *env, jobject, jstring directory, jstring keyword){

			const char *path = env->GetStringUTFChars(directory,NULL);
			const char *key = env->GetStringUTFChars(keyword, NULL);
			struct dirent *entry;
			std::string res;
			DIR *dir = opendir(path);
			if (dir == NULL) {
			   return env->NewStringUTF("No files to display");
			}
			else{

			  while ((entry = readdir(dir)) != NULL) {
			       string st = entry->d_name;
			       string k = key;
			       string direc = path;

			       transform(st.begin(), st.end(), st.begin(), ::tolower);
			       transform(k.begin(), k.end(), k.begin(), ::tolower);
			       if(st.find(k) !=string::npos){
			    	   res = res + "," + st;

			       }

			   }



			   }
			 closedir(dir);
			 return env->NewStringUTF(res.c_str());
}
