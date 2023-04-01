# feb/06/2023 10:04:01 by RouterOS 7.6
# software id = 
#
/interface wireless security-profiles
set [ find default=yes ] supplicant-identity=MikroTik
/ip dhcp-client
add interface=ether1
/system identity
set name=mt-01
