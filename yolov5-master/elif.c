#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<windows.h>

FILE* oldfile;

void input(FILE *file){
    int a = 0;

    // 打开文件
    char buf[1024] = {0};

    while (fgets(buf, sizeof(buf), file) != NULL)
    {
        double nums[10];
        char* token = strtok(buf, " ");  // 使用空格符作为分割符

        int i = 0;
        while (token != NULL) 
        {
        nums[i++] = atof(token);  // 将字符串转换为数字存入数组
        token = strtok(NULL, " ");
        }

        if(nums[0] == 0 || 1){
            a = 1;
        } 
    }

    FILE *fp = NULL;
    fp = fopen("D:/data/yolov5/yolov5data.txt","a");

    if(a == 1)
    {
        fprintf(fp,"\n1");
        fflush(fp);
    }
    else{
        fprintf(fp,"\n0");
        fflush(fp);
    }
    fclose(fp);
}

int main() {
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    FILETIME latestTime;
    char latestFile[256];
    char folderPath[] = "D:/data/yolov5/output/exp/labels/*.txt";

    while(1){
    // 查找文件夹中的第一个文件
    hFind = FindFirstFile(folderPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("无法打开文件夹");
        return 1;
    }

    // 默认将第一个文件设置为最新文件
    latestTime = findData.ftLastWriteTime;
    strcpy(latestFile, findData.cFileName);

    // 遍历文件夹中的其他文件
    while (FindNextFile(hFind, &findData)) {
        // 只处理以 .json 结尾的文件
        if (strstr(findData.cFileName, ".txt") != NULL) {
            // 比较文件的日期和时间
            if (CompareFileTime(&(findData.ftLastWriteTime), &latestTime) > 0) {
                latestTime = findData.ftLastWriteTime;
                strcpy(latestFile, findData.cFileName);
            }
        }
    }

    // 关闭文件查找句柄
    FindClose(hFind);

    // 打开最新的 JSON 文件
    if (strcmp(latestFile, "") != 0) {
        char filePath[256];
        sprintf(filePath, "D:/data/yolov5/output/exp/labels/%s", latestFile);

        printf(latestFile);
        printf("\n");
        FILE* file = fopen(filePath, "r");
        FILE* oldfile = NULL;
        if (file == NULL) {
            printf("无法打开文件");
            return 1;
        }
        
        FILE* fp = NULL;
        fp = fopen("D:/data/yolov5/yolov5data.txt", "a");
        // 在此处读取数据
        // ...
        if(file == oldfile)
            fprintf(fp, "\n0");
        else
            input(file);

        oldfile = file;

        fclose(file);
    }
    Sleep(200);
    }

    return 0;
}