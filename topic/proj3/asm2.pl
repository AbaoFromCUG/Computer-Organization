#!/usr/bin/perl

#Template by CS61C
#Original implementation by Ben Sussman
#Updated implementation by Nathan Kallus

#Updated by Gilbert Chou

print "v2.0 raw\n";
@parsedInsts = ();
%linkTable = ();
while (<>){
    push(@parsedInsts, parseInstruction($_));
}

$index = 0;
foreach $inst (@parsedInsts) {
    printInstruction($inst, $index);
    $index++;
}

# Debug code
#while( my ($k, $v) = each %linkTable ) {
#        print "key: $k, value: $v.\n";
#}

#$inst =~ s/,//g;

#Available instructions
# or, and, add, sub, sllv, srlv, srav, slt, disp, lui, ori, addi, andi, lw, sw, jump, beq, bne, mv, li, nop, stall
# Labels and comments should work
# Indenting and tabbing won't do anything
# For unsigned immediates, hex can be inputed

#Misc stuff
# Labels must start at the beginning of the line. 
# Immediates still can't go over 2^8
# Long jumps/branches not handled
# ori needs to be called like: ori $rd $rs immed


sub parseInstruction{
	my ($inst) = @_;
	my @pInsts = ();	

	if($inst =~m/^(\w+):([^#]*)#?(.*)/i){
	    $linkTable{$1} = scalar(@parsedInsts);
	    $inst = $2;
	}

	if ($inst =~m/^\s*(or|and|add|sub|sllv|srlv|srav|slt)\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
	    @rtypes = qw(or and add sub sllv srlv srav slt);
	    $idx = 0;
	    foreach $ele (@rtypes){ if($ele eq $1) { last; } $idx++ }
	    push(@pInsts, "R $3 $4 $2 $idx");
	}
	elsif ($inst =~m/^\s*disp\s+\$r([0-3]),?\s+(\d+)/i){
	    push(@pInsts, "I 1 $1 0 " . ($2 & 255));
	}
	elsif ($inst =~m/^\s*lui\s+\$r([0-3]),?\s+(0x|0b)?([a-z0-9]+)/i){
	    $num = $3;
	    if($2 eq '0x') {
		$num = hex($3);
	    }
	    
	    push(@pInsts, "I 2 0 $1 " . ($num & 255));
	}
	elsif ($inst =~m/^\s*ori\s+\$r([0-3]),?\s+\$r([0-3]),?\s+(0x|0b)?([a-z0-9]+)/i){
		$num = $4;
		if($3 eq '0x') {
		    $num = hex($4);
		}
		
		push(@pInsts, "I 3 $2 $1 ". ($num & 255)); 
	}
	elsif ($inst =~m/^\s*ori\s+\$r([0-3]),?\s+(0x|0b)?([a-z0-9]+)/i){
		$num = $3;
		if($2 eq '0x') {
		    $num = hex($3);
		}
		
		push(@pInsts, "I 3 $1 $1 ". ($num & 255)); 
	}
	elsif ($inst =~m/^\s*addi\s+\$r([0-3]),?\s+\$r([0-3]),?\s+([-]?)(\d+)/i){
		$num = ($4 & 255);	
		if (length $3 == 1){
			$num = 256 - $num; 
		}

		push(@pInsts, "I 4 $2 $1 $num");
	}
	elsif ($inst =~m/&\s*mv\s+\$r([0-3]),?\s+\$r([0-3])/i) {
		push(@pInsts, "I 5 $1 $1 0");
		push(@pInsts, "I 4 $2 $1 0");	
	}
	elsif ($inst =~m/^\s*andi\s+\$r([0-3]),?\s+\$r([0-3]),?\s+(0x|0b)?([a-z0-9]+)/i){
		$num = $4;
		if($3 eq '0x') {
		    $num = hex($4);
		}
		
		push(@pInsts, "I 5 $2 $1 ". ($num & 255));
	}
	elsif ($inst =~m/^\s*lw\s+\$r([0-3]),?\s+([-]?)(\d+)\(\$r([0-3])\)/i){
		$num = $3;
		if (length $2 == 1) {
			$num = 256 - $num;
		}
		push(@pInsts, "I 6 $4 $1 $num");
	}
	elsif ($inst =~m/^\s*sw\s+\$r([0-3]),?\s+([-]?)(\d+)\(\$r([0-3])\)/i){
		$num = $3;
		if (length $2 == 1) {
			$num = 256 - $num;
		}
		push(@pInsts, "I 7 $4 $1 $num");
	}
	elsif ($inst =~m/^\s*j(ump)?\s+(\w+)/i){
		$temp = $2;
		if(&isnum($2)){
			$temp = ($2 & 4095);
		}

		push(@pInsts, "J 8 $temp");
	}
	elsif ($inst =~m/^\s*beq\s+\$r([0-3]),?\s+\$r([0-3]),?\s+([-]?)(\w+)/i){
		$temp = $4;
		if (&isnum($4)){
			$temp = (length $3 == 0)? ($4 & 255) : 256 - ($4 & 255);
		}
		
		push(@pInsts, "I 9 $1 $2 $temp"); 
	}
	elsif ($inst =~m/^\s*bne\s+\$r([0-3]),?\s+\$r([0-3]),?\s+([-]?)(\w+)/i){
		$temp = $4;
		if (&isnum($4)){
			$temp = (length $3 == 0)? $4 & 255 : 256 - ($4 & 255);
		}
		
		push(@pInsts, "I 10 $1 $2 $temp");
	}
	elsif ($inst =~m/^\s*nop\s*/i) {
		push(@pInsts, "R 0 0 0 0");
	}
	elsif ($inst =~m/^\s*li\s*\$r[(0-3)],?\s+([-]?)(\d+)/i){
		$temp = $3 & 255;
		if (length $2 == 0){
			$temp = 256 - $temp;
		}

		push(@pInsts, "I 5 $1 $1 0");
		push(@pInsts, "I 4 $1 $1 $temp");
	}
	elsif ($inst =~m/^\s*stall\s*/i) {
		push(@pInsts, "I 9 0 0 255");
	}
	elsif ($inst =~/^\s*$/i){

	}
	else {
		push(@pInsts, "R 0 0 0 0");
	}
		

	return @pInsts;
}

sub printInstruction{
	my ($inst, $inst_num) = @_;
	my $num = 0;
	my @array = split(/ /, $inst);

	if($array[0] eq 'R'){
		$num = ($array[1] << 10) | ($array[2] << 8) | ($array[3] << 6) | $array[4];
	}
	elsif ($array[0] eq 'I'){
		$imm = $array[4];
		if($array[1] == 9 || $array[1] == 10){
			if(!&isnum($array[4])){
				if(!$linkTable{$array[4]}){
					print "\nERROR: The next instruction's label doesn't exist - $array[4]\n";
				}

				$imm = (($linkTable{$array[4]} - $inst_num - 1) & 255);
			}	
		}
		
		$num = ($array[1] << 12) | ($array[2] << 10) | ($array[3] << 8) | $imm;
	}
	elsif ($array[0] eq 'J'){
		$addr = $array[2];
		if(!&isnum($array[2])) {
			if(!$linkTable{$array[2]}){
				print "\nERROR: The next instruction's label doesn't exist - $array[2]\n";
			}
			$addr = $linkTable{$array[2]} & 4095;
		}

		$num = ($array[1] << 12) | $addr;
	}

	printf("%x\n", $num);
}

sub isnum{
	my ($num) = @_;
	return ($num =~ m/^\d+$/) ? 1 : 0;
}
