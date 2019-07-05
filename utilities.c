int frequency (const char * name){
    const char * str = name;
    int freq = 0;

for(int i = 0; str[i] != '\0'; ++i){
        if (str[i]=='/')
           ++freq;
   }
    return freq;
}

void usr (char * path, char * user){
    char * str = path;
    int freq = 0;

int i = 0;
for(i=i; str[i] != '\0'; ++i){
        if (str[i]=='/')
           ++freq;
        if (freq == 2)
            break;
   }

int j = 0;
i = i+1;
for(i=i; str[i] != '/'; ++i){
    user[j] = str[i];
    j++;
}
user[j]='\0';

}