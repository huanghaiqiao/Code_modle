修改环境："/etc/profile" "/etc/environment"
exprot http_proxy=http://child-prc.intel.com:913
exprot https_proxy=http://child-prc.intel.com:913

修改apt-get代理，touch "/etc/apt/apt.conf.d/proxy.conf"
追加
Acquire::http::Proxy "http://child-prc.intel.com:913";
Acquire::https::Proxy "http://child-prc.intel.com:913";
