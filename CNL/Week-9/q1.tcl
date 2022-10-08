set ns [new Simulator]
set n0 [$ns node]
set n1 [$ns node]
set tracefile [open out.tr w]
$ns trace-all $tracefile
set namfile [open out.nam w]
$ns namtrace-all $namfile
$ns duplex-link $n0 $n1 10MB 10ms DropTail

#Step 14 Setup a UDP connection
set udp [new Agent/UDP]
$ns attach-agent $n0 $udp

#Step 15 If we setup udp traffic source then connect it with null
set null [new Agent/Null]
$ns attach-agent $n1 $null
$ns connect $udp $null
$udp set fid_ 1

#Step 16 Setting up a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false

#Step 17 Scheduling events for the CBR and FTP agents
$ns at 0.1 "$cbr start"
# $ns at 1.0 "$ftp start"
# $ns at 4.0 "$ftp stop"
$ns at 4.5 "$cbr stop"
$ns at 5.0 "finish"


proc finish {} {
	global ns tracefile namfile
	exec nam out.nam &;
	exit 0
}
$ns run
