prueba_lwescalado:	addi		$s0, $zero, 16
				addi		$s1, $zero, 20
				addi		$s2, $zero, 100
				sw		$s2, 96($zero)
				lwescalado	$s3, $s1, 4, $s0
