#define _WIN32_WINDOWS 0x0410
#define WINVER 0x0400

#include <windows.h>
#include <stdio.h>

void main(void)
{
    const int nTimerUnitsPerSecond = 10000000;
    int cAbrasionCount = 0;
    SYSTEMTIME st;
    LARGE_INTEGER li;

    HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);

    printf("\nConsole application with WaitableTimer by Andrew Dyagel");
    printf("\nFirst timeout after 7 seconds, then every 3 seconds\n\n");
    GetLocalTime(&st);
    printf("Start time: \t\t%.2d:%.2d:%.2d\n\n", st.wHour, st.wMinute, st.wSecond);
    li.QuadPart = -(7 * nTimerUnitsPerSecond);
    if(SetWaitableTimer(hTimer, &li, 3 * 1000, NULL, NULL, FALSE))
    {
        while(TRUE)
        {
            WaitForSingleObject(hTimer, INFINITE);
            GetLocalTime(&st);
            cAbrasionCount++;
            printf("Time have passed since beginning, seconds: %.2d\n", 7 + 3 * cAbrasionCount);
        }
    }
}