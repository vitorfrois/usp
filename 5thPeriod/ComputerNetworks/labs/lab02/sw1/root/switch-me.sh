brctl addbr br0
brctl addif br0 eth0
brctl addif br0 eth1
brctl addif br0 eth2
brctl addif br0 eth3
ifconfig eth0 0.0.0.0
ifconfig eth1 0.0.0.0
ifconfig eth2 0.0.0.0
ifconfig eth3 0.0.0.0
ifconfig br0 192.168.1.10 netmask 255.255.255.0 broadcast 192.168.1.255
