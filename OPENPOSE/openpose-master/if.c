#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>
#include "cJSON.h"

FILE* oldfile;

double data[75];
int j = 0;

void input(FILE *file){

    // ���ļ�
    char buf[10240] = {0};
    fread(buf,1,sizeof(buf),file);
    cJSON* root = cJSON_Parse(buf);
    cJSON* subobj = cJSON_GetObjectItem(root,"people");

    int a;
    cJSON *person = NULL;
    cJSON *item = NULL;
    cJSON *pose_keypoints_2d = NULL;
    person = cJSON_GetArrayItem(subobj,0); 
    pose_keypoints_2d = cJSON_GetObjectItem(person,"pose_keypoints_2d");

        for (int i = 0; i < cJSON_GetArraySize(pose_keypoints_2d); ++i)
        {
            item = cJSON_GetArrayItem(pose_keypoints_2d, i);
            //printf("%f \n",item->valuedouble);
            data[j] = item->valuedouble;
            ++j;
        }

        FILE* fp = NULL;
        fp = fopen("D:/data/openpose/openposedata.txt", "w");
        //if (data[0] != 0) {
            if ((data[31] < data[25] + 200 && data[31] > data[25] - 200) || (data[40] < data[25] + 200 && data[40] > data[25] - 200))
            {
                fprintf(fp, "\n1");
                fflush(fp);
                printf("1\n");
            }
            else {
                fprintf(fp, "\n0");
                fflush(fp);
                printf("0\n");
            }
        //}
        fclose(fp);
    
 
    cJSON_Delete(root);
    fclose(file);
}

int main() {
    WIN32_FIND_DATA findData;
    HANDLE hFind;
    FILETIME latestTime;
    char latestFile[256];
    char folderPath[] = "D:/data/openpose/output/*.json";

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
        if (strstr(findData.cFileName, ".json") != NULL) {
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
        sprintf(filePath, "D:/data/openpose/output/%s", latestFile);

        printf(latestFile);
        printf("\n");
        FILE* file = fopen(filePath, "r");
        if (file == NULL) {
            printf("�޷����ļ�");
            return 1;
        }
        

        // �ڴ˴���ȡ����
        // ...
        if (file != oldfile)
            input(file);

        oldfile = file;

        fclose(file);
    }
    Sleep(500);
    }

    return 0;
}