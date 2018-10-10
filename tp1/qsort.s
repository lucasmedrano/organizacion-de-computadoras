#include <mips/regdef.h>

        .text
        .align 2
        .globl qsort
        .ent qsort
qsort:
        .set noreorder
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
        subu    $9, $17, $16       # if (der < izq){
        bltz    $9, swap2          # swap2}

        add     $18, $0, $4        # s2 <- inicio
        add     $19, $0, $5        # s3 <- fin

while1: subu    $10, $18, $19       # if (inicio >= fin) {
        bgtz    $10, swap2          #  swap2;
        be      $18, $19, swap2     # }

while2: subu    $10, $17, $18       # if (inicio >= der){
        bltz    $10, while3         #  while3
        be      $17, $18, while3    # }

        add     $4, $0, $18        # Cargo inicio e izq
        add     $5, $0, $16        # y num para
        add     $6, $0, $20        # comparar
        j       comparar            #Compara *inicio y *izq segun num y devuelve en $v0
        bltz    $2, aumentar_inicio
        be      $2, $0, aumentar_inicio
        ba      while2

while3: subu    $10, $19, $16       # if(fin <= izq){
        bltz    $10, swap1          #   swap1
        be      $16, $19, swap1     # }

        add     $4, $0, $17        # Cargo der para comparar
        j       comparar
        bgtz    $2, decrementar_fin
        ba      while3

swap1:  lw      $11, 0($18)         #Swap inicio-fin
        lw      $12, 0($19)
        sw      $11, 0($18)
        sw      $12, 0($19)
        ba      while1

swap2:  lw      $11, 0($16)         #Swap izq-fin
        lw      $12, 0($19)
        sw      $11, 0($19)
        sw      $12, 0($16)

        subi    $19, 1              # qsort(izq, fin-1, num)
        add     $4, $0, $16
        add     $5, $0, $19
        add     $6, $0, $20
        j       qsort

        addi    $19, 2              # qsort(fin+1, der, num)
        add     $4, $0, $19
        add     $5, $16, $17
        addi    $6, $0, $20
        j       qsort

comparar:   subu    $sp, $sp, 8
            sw      $fp, 4($sp)
            sw      $gp, 0($sp)

            sw      $4, 8($sp)
            sw      $5, 12($sp)
            sw      $6, 16($sp)

            bz      $6, atoi
            lw      $9, 0(?)               #Que registro iba aca?
            lw      $10, 0(?)
loop:       lb      $11, 0($t1)
            lb      $12, 0($t2)
            subu    $13, $11, $12
            bltz    $13, dev_menor
            bgtz    $13, dev_mayor
            be      $11, $0, dev_cero       #habria que hacer una funcion comparar_numeros, porque esto con numeros no anda
            ba      loop

atoi:       add     $2, $2, $0
            addi    $12, $0, 10     #t4 <-- 10
            mov     $8, $4
loop2:      lbu     $9, 0($8)
            be      $9, $0, fin     #falta fin
            sub     $10, $9, $0
            mul     $2, $2, $12
            add     $2, $2, $12
            addi    $8, $8, 1
            ba      loop2

            lw      $fp, 12($sp)
            lw      $gp, 8($sp)
            jr      $ra
            addr    $sp, $sp, 16