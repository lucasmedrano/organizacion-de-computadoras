qsort:  subu    $sp, $sp, 32
        sw      ra, 24($sp)
        sw      fp, 20($sp)
        sw      gp, 16($sp)

        sw      $a0, 32($sp)
        sw      $a1, 36($sp)
        sw      $a2, 40($sp)

        add     $s0, $0, $a0        # s0 <- izq
        add     $s1, $0, $a1        # s1 <- der
        add     $s4, $0, $a2        # s4 <- num
        subu    $t1, $s1, $s0       # if (der < izq){
        bneg    $t1, swap2          # swap2}

        add     $s2, %0, $a0        # s2 <- inicio
        add     $s3, $0, $a1        # s3 <- fin

while1: subu    $t2, $s2, $s3       # if (inicio >= fin) {
        bpos    $t2, swap2          #  swap2;
        be      $s2, $s3, swap2     # }

while2: subu    $t2, $s1, $s2       # if (inicio >= der){
        bneg    $t2, while3         #  while3
        be      $s1, $s2, while3    # }

        add     $a0, $0, $s2        # Cargo inicio e izq
        add     $a1, $0, %s0        # y num para
        add     $a2, $0, $s4        # comparar
        j       comparar            #Compara *inicio y *izq segun num y devuelve en $v0
        bneg    $v0, aumentar_inicio
        be      $v0, $0, aumentar_inicio
        ba      while2

while3: subu    $t2, $s3, $s0       # if(fin <= izq){
        bneg    $t2, swap1          #   swap1
        be      $s0, $s3, swap1     # }

        add     $a0, $0, $s3        # Cargo der para comparar
        j       comparar
        bpos    $v0, decrementar_fin
        ba      while3

swap1:  lw      $t3, 0($s2)         #Swap inicio-fin
        lw      $t4, 0($s3)
        sw      $t3, 0($s3)
        sw      $t4, 0($s2)
        ba      while1

swap2:  lw      $t3, 0($s0)         #Swap izq-fin
        lw      $t4, 0($s3)
        sw      $t3, 0($s3)
        sw      $t4, 0($s0)

        subi    $s3, 1              # qsort(izq, fin-1, num)
        add     $a0, $0, $s0
        add     $a1, $0, $s3
        add     $a2, $0, $s4
        j       qsort

        addi    $s3, 2              # qsort(fin+1, der, num)
        add     $a0, $0, $s3
        add     $a1, $s0, $s1
        addi    $a2, $0, $s4
        j       qsort
