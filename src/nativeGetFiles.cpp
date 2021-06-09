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


jobject JNICALL Java_controllers_GetFiles_getFiles
  (JNIEnv *env, jobject thisObj, jstring directory, jstring keyword){

		const char *path = env->GetStringUTFChars(directory,NULL);
		const char *key = env->GetStringUTFChars(keyword, NULL);

		//loading the calling class object
		jclass thisClass = env->GetObjectClass(thisObj);

	   //calling the class method
		jmethodID addFileMethod = env->GetMethodID(thisClass,
	                                  "addFile", "(Ljava/lang/String;)V");
		//setting up string and array-list class and initializing
			jclass classString = env->FindClass("java/lang/String");
			jmethodID midStringInit = env->GetMethodID(classString, "<init>", "(Ljava/lang/String;)V");
				   if (NULL == midStringInit) return NULL;
			jclass arrayList = env->FindClass("java/util/ArrayList");
			  if (arrayList == NULL)   return NULL;

			jmethodID mid_init =  env->GetMethodID(arrayList, "<init>", "()V");
			  if (mid_init == NULL) return NULL;

			jobject fileList = (env->NewObject(arrayList, mid_init));
			  if (fileList == NULL) return NULL;

			 jmethodID mid_add = env->GetMethodID(arrayList, "add", "(Ljava/lang/Object;)Z");
			  if (mid_add == NULL) return NULL;

			  jint flag = 0;
			  jstring notFound = env->NewStringUTF("NULL");
			  jobject fileNotFoundString = env->NewObject(classString, midStringInit, notFound);
	    struct dirent *entry;
	    DIR *dir = opendir(path);
	    if (dir == NULL) {
	    	  //jstring notFound = env->NewStringUTF("NULL");
	    	  env->CallVoidMethod(thisObj, addFileMethod, notFound);
	    	  jboolean jbool = env->CallBooleanMethod(fileList, mid_add, fileNotFoundString);
	    	  	    	    if (jbool == false) return NULL;
	    }
	    else{
	    	while ((entry = readdir(dir)) != NULL) {
	      	       string st = entry->d_name;
	      	       string k = key;
	      	       string direc = path;

	      	       transform(st.begin(), st.end(), st.begin(), ::tolower);
	      	       transform(k.begin(), k.end(), k.begin(), ::tolower);
	      	       if(st.find(k) !=string::npos){
	      	    	   cout<< "inside cpp" << endl;
	      	    	 //jstring fileName = env->NewStringUTF(entry->d_name);
	      	    	 flag = 1;
	      	    	 jstring fileName = env->NewStringUTF(entry->d_name);
	      	    	 jobject file = env->NewObject(classString, midStringInit, fileName);
	      	    	 jboolean jbool = env->CallBooleanMethod(fileList, mid_add, file);
	      	    	 	 if (jbool == false) return NULL;
	      	    	 env->CallVoidMethod(thisObj, addFileMethod, fileName);

	      	       }

	      	   }
	    	if(flag == 0){
	    		jboolean jbool = env->CallBooleanMethod(fileList, mid_add, fileNotFoundString);
	    			if (jbool == false) return NULL;
	    	}
	      }


	   return fileList;
}


