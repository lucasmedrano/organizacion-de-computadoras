prueba_lwescalado:	addi		$s0, $zero, 16
				addi		$s1, $zero, 20
				addi		$s2, $zero, 100
				
				sw		$s2, 96($zero)
				lwescalado	$s3, $s1, 4, $s0

				beq		$s3, $s2, prueba_pasada
				b		prueba_fallida

prueba_pasada:		add		$v0, $zero, $zero
				b 		fin
prueba_fallida:	addi		$v0, $zero, 1
fin:
				
