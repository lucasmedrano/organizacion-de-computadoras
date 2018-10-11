        .text
        .align 2
        .globl orgaqsortassembly
        .ent orgaqsortassembly
        
orgaqsortassembly:  .set noreorder
        .cpload $25
        .set reorder      
		subu    $sp, $sp, 32
        sw      $ra, 24($sp)
        sw      $fp, 20($sp)
        sw      $gp, 16($sp)

        sw      $4, 32($sp)
        sw      $5, 36($sp)
        sw      $6, 40($sp)

        add     $16, $0, $4        # s0 <- izq
        add     $17, $0, $5        # s1 <- der
        add     $20, $0, $6        # s4 <- num
        subu    $9, $17, $16       # if (der <= izq){
        blez    $9, end            # end}

        add     $18, $0, $4        # s2 <- inicio
        add     $19, $0, $5        # s3 <- fin


while1: subu    $10, $18, $19       # if (inicio >= fin) {
        bgez    $10, swap2          #  swap2 }

while2: subu    $10, $17, $18       # if (inicio >= der){
        blez    $10, while3         #  while3}

        add     $4, $0, $18         # Cargo inicio e izq
        add     $5, $0, $16         # y num para
        add     $6, $0, $20         # comparar
        jal     comparar            # Compara *inicio y *izq segun num y devuelve en $v0
        blez    $2, aumentar_inicio

while3: subu    $10, $19, $16       # if(fin <= izq){
        blez    $10, if       	    #   swap1}

        add     $4, $0, $19         # Cargo der para comparar
        add		$5, $0, $16
        add		$6, $0, $20
        jal     comparar
        bgtz    $2, decrementar_fin
        
if:		subu	$10, $18, $19
		bltz	$10, swap1
		b		while1

swap1:  la		$21, 0($18)
		la		$22, 0($19)
		lw      $11, 0($21)         #Swap inicio-fin
        lw      $12, 0($22)
        sw      $11, 0($22)
        sw      $12, 0($21)
        b       while1

swap2:  la		$21, 0($16)
		la		$22, 0($19)
		lw      $11, 0($21)         #Swap izq-fin
        lw      $12, 0($22)
        sw      $11, 0($22)
        sw      $12, 0($21)


        addi    $19, $19, -4             # qsort(izq, fin-1, num)
        add     $4, $0, $16
        add     $5, $0, $19
        add     $6, $0, $20
        jal     orgaqsortassembly

        addi    $19, $19, 8              # qsort(fin+1, der, num)
        add     $4, $0, $19
        add     $5, $16, $17
        add     $6, $0, $20
        jal     orgaqsortassembly

end:	lw		$ra, 24($sp)
        lw		$fp, 20($sp)
        lw		$gp, 16($sp)
        addiu	$sp, $sp, 32
        j		$ra

decrementar_fin:    addi   $19, $19, -4
                    b      while3

aumentar_inicio:    addi    $18, $18, 4
                    b      while2
         .end    orgaqsortassembly

			.text
			.align 2
			.globl comparar
			.ent comparar
comparar:   .set noreorder
			.cpload $25
			.set reorder
			subu    $sp, $sp, 8
            sw      $fp, 4($sp)
            sw      $gp, 0($sp)

            sw      $4, 8($sp)
            sw      $5, 12($sp)
            sw      $6, 16($sp)

            la		$14, 0($4)
            la		$15, 0($5)
            lw      $9, 0($14)
            lw      $10, 0($15)
loop:       lbu     $11, 0($9)
            lbu     $12, 0($10)

            subu    $13, $11, $12
            bltz    $13, dev_menor
            bgtz    $13, dev_mayor
            beq     $11, $0, dev_cero       #habria que hacer una funcion comparar_numeros, porque esto con numeros no anda

            addi    $9, $9, 1
            addi    $10, $10, 1

            add     $11, $0, $0
            add     $11, $0, $0
            b       loop

fin:        lw      $fp, 4($sp)
            lw      $gp, 0($sp)
            addi    $sp, $sp, 8
            j       $ra

dev_cero:   add     $2, $0, $0
            b fin

dev_menor:  addi     $2, $0, -1
            b fin

dev_mayor:  addi    $2, $0, 1
            b fin
            
            .end comparar
