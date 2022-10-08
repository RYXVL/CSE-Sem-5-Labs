set ns [new Simulator]
$ns color 1 green
$ns color 2 Red
set nt [open simulate.nam w]
$ns namtrace-all $nt
set tr [open simulate.tr w]
$ns trace-all $tr
proc finish {} {
	global ns nt tr
	$ns flush-trace
	#Close the NAM trace file
	close $nt
	close $tr
	exec nam simulate.nam &
	exit 0
}
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
$ns duplex-link $n1 $n2 2Mb 20ms DropTail
$ns duplex-link $n3 $n4 1Mb 10ms DropTail
set tcp1 [new Agent/TCP]
$tcp1 set class_ 1
$ns attach-agent $n1 $tcp1
set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $tcp1 $sink
$tcp1 set fid_ 1
set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP
set tcp2 [new Agent/TCP]
$tcp2 set class_ 2
$ns attach-agent $n3 $tcp2
set sink [new Agent/TCPSink]
$ns attach-agent $n4 $sink
$ns connect $tcp2 $sink
$tcp2 set fid_ 2
set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP
$ns at 0.0 "$ftp1 start"
$ns at 0.0 "$ftp2 start"
$ns at 4.0 "$ftp1 stop"
$ns at 4.0 "$ftp2 stop"
$ns at 5.0 "finish"
$ns run
