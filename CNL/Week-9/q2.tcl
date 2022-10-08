set ns [new Simulator]
set n0 [$ns node]
set n1 [$ns node]
set tracefile [open out.tr w]
$ns trace-all $tracefile
set namfile [open out.nam w]
$ns namtrace-all $namfile
$ns duplex-link $n0 $n1 10MB 10ms DropTail
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set tcpsink0 [new Agent/TCPSink]
$ns attach-agent $n1 $tcpsink0
set ftp [new Application/FTP]
$ftp attach-agent $tcp0
$ns connect $tcp0 $tcpsink0
$ns at 0.0 "$ftp start"
$ns at 4.0 "finish"
proc finish {} {
	global ns tracefile namfile
	exec nam out.nam &;
	exit 0
}
$ns run
