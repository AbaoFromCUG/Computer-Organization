#!/usr/bin/perl

#Template by CS61C
#Original implementation by Ben Sussman
#Updated implementation by Nathan Kallus

print "v2.0 raw\n";
while (<>){
        printInstruction($_);
}

#$inst =~ s/,//g;

sub printInstruction(){
	my ($inst) = @_;
	$num = 0;
	if ($inst =~m/^\s*or\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
		$num = ($1 << 6) | ($2 << 10) | ($3 << 8) | 0; 
	}
	elsif ($inst =~m/^\s*and\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
		$num = ($1 << 6) | ($2 << 10) | ($3 << 8) | 1; 
	}
	elsif ($inst =~m/^\s*add\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
		$num = ($1 << 6) | ($2 << 10) | ($3 << 8) | 2; 
	}
	elsif ($inst =~m/^\s*sub\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
		$num = ($1 << 6) | ($2 << 10) | ($3 << 8) | 3; 
	}
	elsif ($inst =~m/^\s*sllv\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
		$num = ($1 << 6) | ($2 << 10) | ($3 << 8) | 4; 
	}
	elsif ($inst =~m/^\s*srlv\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
		$num = ($1 << 6) | ($2 << 10) | ($3 << 8) | 5; 
	}
	elsif ($inst =~m/^\s*srav\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
		$num = ($1 << 6) | ($2 << 10) | ($3 << 8) | 6; 
	}
	elsif ($inst =~m/^\s*slt\s+\$r([0-3]),?\s+\$r([0-3]),?\s+\$r([0-3])/i){
		$num = ($1 << 6) | ($2 << 10) | ($3 << 8) | 7; 
	}
	elsif ($inst =~m/^\s*disp\s+\$r([0-3]),?\s+(\d+)/i){
		$num = (1 << 12) | ($1 << 10) | ($2 & 255); 
	}
	elsif ($inst =~m/^\s*lui\s+\$r([0-3]),?\s+(0x)?([a-fA-F0-9]+)/i){
		$num = (2 << 12) | ($1 << 8) | ((length $2 == 0 ? $3 : hex($3)) & 255); 
	}
	elsif ($inst =~m/^\s*ori\s+\$r([0-3]),?\s+\$r([0-3]),?\s+(0x)?([a-fA-F0-9]+)/i){
		$num = (3 << 12) | ($1 << 8) | ($2 << 10) | ((length $3 == 0 ? $4 : hex($4)) & 255); 
	}
	elsif ($inst =~m/^\s*addi\s+\$r([0-3]),?\s+\$r([0-3]),?\s+(-?)(0x)?([a-fA-F0-9]+)/i){
		$num = (4 << 12) | ($1 << 8) | ($2 << 10) | (((length $3 == 0 ? "" : "-").(length $4 == 0 ? $5 : hex($5))) & 255); 
	}
	elsif ($inst =~m/^\s*andi\s+\$r([0-3]),?\s+\$r([0-3]),?\s+(0x)?([a-fA-F0-9]+)/i){
		$num = (5 << 12) | ($1 << 8) | ($2 << 10) | ((length $3 == 0 ? $4 : hex($4)) & 255); 
	}
	elsif ($inst =~m/^\s*lw\s+\$r([0-3]),?\s+(-?)(0x)?([a-fA-F0-9]+)\(\$r([0-3])\)/i){
		$num = (6 << 12) | ($1 << 8) | (((length $2 == 0 ? "" : "-").(length $3 == 0 ? $4 : hex($4))) & 255) | ($5 << 10); 
	}
	elsif ($inst =~m/^\s*sw\s+\$r([0-3]),?\s+(-?)(0x)?([a-fA-F0-9]+)\(\$r([0-3])\)/i){
		$num = (7 << 12) | ($1 << 8) | (((length $2 == 0 ? "" : "-").(length $3 == 0 ? $4 : hex($4))) & 255) | ($5 << 10); 
	}
	elsif ($inst =~m/^\s*j(ump)?\s+(0x)?([a-fA-F0-9]+)/i){
		$num = (8 << 12) | ((length $2 == 0 ? $3 : hex($3)) & 4095); 
	}
	elsif ($inst =~m/^\s*beq\s+\$r([0-3]),?\s+\$r([0-3]),?\s+(-?)(0x)?([a-fA-F0-9]+)/i){
		$num = (9 << 12) | ($1 << 10) | ($2 << 8) | (((length $3 == 0 ? "" : "-").(length $4 == 0 ? $5 : hex($5))) & 255); 
	}
	elsif ($inst =~m/^\s*bne\s+\$r([0-3]),?\s+\$r([0-3]),?\s+(-?)(0x)?([a-fA-F0-9]+)/i){
		$num = (10 << 12) | ($1 << 10) | ($2 << 8) | (((length $3 == 0 ? "" : "-").(length $4 == 0 ? $5 : hex($5))) & 255); 
	}

	printf("%x\n", $num);
}