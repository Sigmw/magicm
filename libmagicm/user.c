#include "../magicm.h"
#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>

char* user() {
    int uid;
    struct passwd *user_info;
    char* info = malloc(1024);

    uid = getuid();
    user_info = getpwuid(uid);
    sprintf(info, "User name: %s\nUser UID: %i\nUser GID: %i\nUser home directory: %s\nUser shell: %s", user_info->pw_name, user_info->pw_uid, user_info->pw_gid, user_info->pw_dir, user_info->pw_shell);

    return info;
}
