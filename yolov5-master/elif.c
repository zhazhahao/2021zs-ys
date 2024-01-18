#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include<windows.h>

FILE* oldfile;

void input(FILE *file){
    int a = 0;

    // ���ļ�
    char buf[1024] = {0};

    while (fgets(buf, sizeof(buf), file) != NULL)
    {
        double nums[10];
        char* token = strtok(buf, " ");  // ʹ�ÿո����Ϊ�ָ��

        int i = 0;
        while (token != NULL) 
        {
        nums[i++] = atof(token);  // ���ַ���ת��Ϊ���ִ�������
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
    // �����ļ����еĵ�һ���ļ�
    hFind = FindFirstFile(folderPath, &findData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("�޷����ļ���");
        return 1;
    }

    // Ĭ�Ͻ���һ���ļ�����Ϊ�����ļ�
    latestTime = findData.ftLastWriteTime;
    strcpy(latestFile, findData.cFileName);

    // �����ļ����е������ļ�
    while (FindNextFile(hFind, &findData)) {
        // ֻ������ .json ��β���ļ�
        if (strstr(findData.cFileName, ".txt") != NULL) {
            // �Ƚ��ļ������ں�ʱ��
            if (CompareFileTime(&(findData.ftLastWriteTime), &latestTime) > 0) {
                latestTime = findData.ftLastWriteTime;
                strcpy(latestFile, findData.cFileName);
            }
        }
    }

    // �ر��ļ����Ҿ��
    FindClose(hFind);

    // �����µ� JSON �ļ�
    if (strcmp(latestFile, "") != 0) {
        char filePath[256];
        sprintf(filePath, "D:/data/yolov5/output/exp/labels/%s", latestFile);

        printf(latestFile);
        printf("\n");
        FILE* file = fopen(filePath, "r");
        FILE* oldfile = NULL;
        if (file == NULL) {
            printf("�޷����ļ�");
            return 1;
        }
        
        FILE* fp = NULL;
        fp = fopen("D:/data/yolov5/yolov5data.txt", "a");
        // �ڴ˴���ȡ����
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