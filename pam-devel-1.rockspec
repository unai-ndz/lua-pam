package = "pam"
version = "devel-1"
source = {
   url = "git://github.com/unai-ndz/lua-pam",
   tag = "rockspec"
}
description = {
   summary = "A module for lua to use PAM",
   detailed = "A module for lua to use PAM",
   homepage = "https://github.com/RMTT/lua-pam",
   license = ""
}
supported_platforms = {
   "linux"
}
dependencies = {
   "lua >= 5.1"
}
build = {
   type = "cmake",
   variables = {
      CMAKE_INSTALL_PREFIX="$(PREFIX)"
   }
}