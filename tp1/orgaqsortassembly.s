    .text
    .align 2
    .globl orgaqsortassembly
    .ent orgaqsortassembly

orgaqsortassembly:  .set noreorder
                    .cpload $25
                    .set reorder

        subu    $sp, $sp, 48
        sw      $ra, 40($sp)
        sw      $fp, 36($sp)
        sw      $gp, 32($sp)

        sw      $4, 48($sp)
        sw      $5, 52($sp)
        sw      $6, 56($sp)

        subu    $8, $4, $5      # if (izq > der) {
        bgtz    $8, end       # end }

        add     $16, $0, $4     # $16 <- izq
        add     $17, $0, $5     # $17 <- der
        add     $18, $0, $4     # $18 <- inicio
        add     $19, $0, $5     # $19 <- fin
        add    $20, $0, $6      # $20 <- num

while1: subu    $8, $18, $19        # if(inicio >= fin){
        bgez    $8, swap2           # swap2 }

while2: subu    $8, $18, $17
        bgez    $8, while3

        add     $4, $0, $18
        add     $5, $0, $16
        jal     comparar
        blez    $2, aumentar_inicio

while3: subu    $8, $19, $16
        blez    $8, swap1
        add     $4, $0, $19
        add     $5, $0, $16
        jal     comparar
        bgtz    $2, decrementar_fin

swap1:  subu    $8, $18, $19
        bgez    $8, while1

        la		$21, 0($18)
        la     	$22, 0($19)
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

llamada_rec_1:  sw      $16, 16($sp)     # izq al ABA
                sw      $17, 20($sp)     # der al ABA
                sw      $18, 24($sp)     # inicio al ABA
                sw      $19, 28($sp)     # fin al ABA

                addi    $19, $19, -4
                add     $4, $0, $16
                add     $5, $0, $19
                jal     orgaqsortassembly

llamada_rec_2:  lw      $19, 28($sp)
                lw      $17, 20($sp)

                addi    $19, $19, 4
                add     $4, $0, $19
                add     $5, $0, $17
                jal     orgaqsortassembly

end:            lw      $ra, 40($sp)
                lw      $fp, 36($sp)
                lw      $gp, 32($sp)
                addi    $sp, $sp, 48
                jr     $ra

aumentar_inicio:    addi    $18, $18, 4
                    b       while2

decrementar_fin:    addi    $19, $19, -4
                    b       while3

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
loop:   lbu     $11, 0($9)
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

fin:    lw      $fp, 4($sp)
        lw      $gp, 0($sp)
        addi    $sp, $sp, 8
        jr       $ra

dev_cero:   add     $2, $0, $0
            b fin

dev_menor:  addi     $2, $0, -1
            b fin

dev_mayor:  addi    $2, $0, 1
            b fin

    .end comparar
