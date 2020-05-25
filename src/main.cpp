#include <lua.hpp>
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <pwd.h>

#ifndef luaL_newlibtable
#  define luaL_newlibtable(L, l) \
  (lua_createtable((L), 0, sizeof((l))/sizeof(*(l))-1))
#endif
#ifndef luaL_newlib
#  define luaL_newlib(L, l) \
  (luaL_newlibtable((L), (l)), luaL_register((L), NULL, (l)))
#endif

struct pam_response *reply;

int simple_conversation(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr) {
    *resp = reply;
    return PAM_SUCCESS;
}


static int auth_current_user(lua_State *L) {
    int retval;

    const char *pass = luaL_checkstring(L, -1);

    uid_t uid = getuid();
    passwd *pw = getpwuid(uid);
    const char *user = pw->pw_name;

    pam_handle_t *pamh = NULL;
    struct pam_conv conv = {
            simple_conversation,
            NULL
    };
    retval = pam_start("login", user, &conv, &pamh);

    reply = (struct pam_response *) malloc(sizeof(struct pam_response));

    if (retval == PAM_SUCCESS) {
        reply->resp = strdup(pass);
        reply->resp_retcode = 0;

        retval = pam_authenticate(pamh, 0);
    }

    /* This is where we have been authorized or not. */
    if (retval == PAM_SUCCESS) {
        lua_pushboolean(L, true);
    } else {
        lua_pushboolean(L, false);
    }
    return 1;
}


static const struct luaL_Reg lua_pam[] = {
        {"auth_current_user", auth_current_user},
        {NULL, NULL}  /* sentinel */
};

extern "C" int luaopen_liblua_pam(lua_State *L) {
    luaL_newlib(L, lua_pam);
    return 1;
}
