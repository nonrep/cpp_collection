#include <iostream>

void addToDict(int k, int start, char* dict, const char* string, int& free) {
    int i = 0;
    bool equal = false;
    while (dict[i] != '\0') {
        bool notEq = true;
        int j = 0;
        for (; j < k; j++, i++) {
            if (dict[i] != string[start + j]) {
                notEq = false;
                break;
            }
        }
        if (j != k)
            notEq = false;
        if ((dict[i] == ' ' or dict[i] == '\0') && notEq == true) {
            char t = dict[i];
            equal = true;
            break;
        }
        while(true) {
            char t = dict[i];
            if (t == ' ') {
                i++;
                break;
            }
            if (t == '\0')
                break;
            i++;
        }
    }
    if (!equal) {
        i = free;
        for (int j = 0; j < k; i++, j++)
        {
            dict[i] = string[start + j];
        }
        i+=1;
        dict[i] = '\0';
        free = i;
    }
}

const char* createDict(const char* string) {
    char dict[256];
    for (int i = 1; i < 256; i++)
        dict[i] = ' ';
    dict[255] = '\0';
    dict[0] = '\0';
    int free = 0;
    int i = 0;
    int start = 0;
    while (string[i] != '\0') {
        while (true) {
            char t = string[i];
            if (t == ' ' or t == '\0')
                break;
            i++;
        }

        int k = i - start;
        addToDict(k, start, dict, string, free);
        i++;
        start = i;
    }
    printf("Полученный словарь:\n%s\n", dict);
    return dict;
}


int main() {
    char string[] = "word word cat name cat cats password nam\0";
    char* dict;
    //dict = createDict(string);
    printf("Полученный словарь:\n%s\n", createDict(string));
}