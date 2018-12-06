prueba_andi:	addi		$s0, $zero, 10			#Variable para la andi
			andi		$s1, $s0, 75			
			andi		$s2, $s0, 0
			andi		$s3, $s0, 0xffffffff

			beq		$s1, $s0, chequear_s2
			b		prueba_fallida
			
chequear_s2:	beq		$s2, $zero, chequear_s3
			b		prueba_fallida

chequear_s3:	beq		$s2, $zero, prueba_pasada
			b		prueba_fallida
			
prueba_pasada:	add		$v0, $zero, $zero		#La prueba dio el resultado esperado
			b 		fin

prueba_fallida:addi		$v0, $zero, 1			#La prueba no dio el resultado esperado
fin:			nop