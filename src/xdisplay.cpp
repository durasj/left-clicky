#include "xdisplay.h"
#include <stdio.h>  /* For fputs() */
#include <stdlib.h> /* For atexit() */

static Display *mainDisplay = NULL;
static int registered = 0;
static const char *displayName = ":0.0";
static int hasDisplayNameChanged = 0;

char *own_strdup(const char *str)
{
    int len = 0;
    while (str[len])
        len++;
    char *result = (char*)malloc(len + 1);
    char *psrc = str;
    char *pdst = result;
    while (*psrc != 0)
    {
        *pdst = *psrc;
        pdst++;
        psrc++;
    }
    *pdst = '\0';
    return result;
}

Display *XGetMainDisplay(void)
{
    /* Close the display if displayName has changed */
    if (hasDisplayNameChanged)
    {
        XCloseMainDisplay();
        hasDisplayNameChanged = 0;
    }

    if (mainDisplay == NULL)
    {
        /* First try the user set displayName */
        mainDisplay = XOpenDisplay(displayName);

        /* Then try using environment variable DISPLAY */
        if (mainDisplay == NULL)
        {
            mainDisplay = XOpenDisplay(NULL);
        }

        if (mainDisplay == NULL)
        {
            fputs("Could not open main display\n", stderr);
        }
        else if (!registered)
        {
            atexit(&XCloseMainDisplay);
            registered = 1;
        }
    }

    return mainDisplay;
}

void XCloseMainDisplay(void)
{
    if (mainDisplay != NULL)
    {
        XCloseDisplay(mainDisplay);
        mainDisplay = NULL;
    }
}

const char *getXDisplay(void)
{
    return displayName;
}

void setXDisplay(const char *name)
{
    displayName = own_strdup(name);
    hasDisplayNameChanged = 1;
}
