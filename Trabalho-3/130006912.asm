# Trablho 3 
# Bruno Justino Garcia Praciano - 13/0006912

.data
jTable:        		.word L0,L1,L2,L3,L4,L5,L6     #Definição da JumpTable 

str1: 	      		.space 32 				# para reservar 32 caracteres para as strings
str2: 	      		.space 32
result:       		.space 64

msg1:	      		.asciiz "Insira a primeira string\n"
msg2:	      		.asciiz "Insira a segunda string\n"
copia:        		.asciiz "O Conteúdo da string copiada é: \n"

tamanhoString: 		.asciiz "O tamanho da string é: \n"
stringMessage: 		.asciiz "Insira sua string\n"
msgCat:        		.asciiz "A string concatenada é: \n"
stringMessageUpper: 	.asciiz "Insira sua string em letra maiúscula\n"
stringMessageLow: 	.asciiz "Insira sua string em letras minúsculas\n"
convertLow: 		.asciiz "A string convertida para letras minúsculas é:\n"
convertUp: 		.asciiz "A string convertida para letras maiúsculas é:\n"


msg:         		.asciiz "\nEscolha uma opção;\n [1] Para obter o tamanho de uma string\n [2] Para concaternar duas strings\n [3]Para copiar uma string em outra\n [4] Para comparar duas strings\n [5] Para converter a string em minúscula\n [6] Para converter a string em maiúscula\n [0] Para sair\n"

.text
###########################################  Menu #########################################################
userInteraction:
		li  $v0,4           	# Opção para imprimir uma string
		la  $a0,msg         	# Pega o endereço da String
		syscall

		li  $v0,5           	# Realiza a interação do usuário com o menu
		syscall
		
		move $s0,$v0        	# pega a opção selecionada e salva em $s0
		sll $s0,$s0,2       	# $s0=$s0*4 
		la  $t0,jTable      	# Busca o endereço da função selecionada
		add $s0,$s0,$t0     	# $s0+$t0 = Endereço atual para o jump
		lw  $s0,($s0)       	# Carrega o endereço de destini
		jr  $s0             	# Vai para a label selecionada

L0:   
  		li  $v0,10      	#Exit--
		syscall         	#Exit


L1:   
		j   strlen
L2:   
		j   strcat
L3:   
		j   strcpy
L4:   
		j   strcmp 
L5:   
		j   strlwr
L6:   
		j   strupr


########################################### Fim do Menu ######################################################


########################################### Bloco da Função StrLen ###########################################
strlen:		
		li  $v0, 4           	       #Interage com usuário para que ele informe a string
		la  $a0, stringMessage         #Pega o endereço da string
		syscall

		li $v0, 8		       # Salva o valor inserido no console
		la $a0, str1	               # salva o valor de str1 em $a0
		li $a1, 32	               # informa o tamanho da string	
		syscall
		
		li $t0, -1                     # Inicializa o contador com -1, pois tem o caracter '\n'
	
loopStrlen:
		lb 	$t1, 0($a0) 	       # Carrega caracter por caracter em $t1
		beqz 	$t1, printStrlen       # Checa se chegou ao fim
		addi 	$a0, $a0, 1 	       # Incrementa o ponteiro da String
		addi 	$t0, $t0, 1            # Incrementa o contador com o tamanho da string
		j 	loopStrlen 	       # Retorna para o início do loop
		
printStrlen: 	li  $v0,4           	      # Opção para imprimir uma string
		la  $a0,tamanhoString         # Pega o endereço da String
		syscall
		
	        li 	$v0, 1		       # Código do sistema para imprimir inteiros
  		move 	$a0, $t0	       # Move o tamanho da string para $a0
  		syscall
  	        j 	userInteraction	       # Volta para o menu inicial

########################################### Fim do Bloco da Função StrLen ###########################################

########################################### Bloco da Função StrCat ##################################################
strcat:				
		li  	$v0, 4           	       #Interage com usuário para que ele informe a string
		la  	$a0, msg1       	       #Pega o endereço da mensagem
		syscall

		li 	$v0, 8		       	       # Salva o valor inserido no console
		la 	$a0, str1	               # salva o valor de str1 em $a0
		
		li 	$a1, 32	                       # informa o tamanho da string	
		syscall
		move 	$s2, $a0		       #salva o valor de $a0 em $s2
		
		li  	$v0, 4           	       # Interage com usuário para que ele informe a string
		la  	$a0, msg2       	       # Pega o endereço da mensagem
		syscall

		li 	$v0, 8		       	       # Salva o valor inserido no console
		la 	$a0, str2	               # Salva o valor de str2 em $a0
		
		li 	$a1, 32	                       # informa o tamanho da string	
		syscall
		move 	$s3, $a0		       # Salva o valor de $a0 em $s3
		
		la 	$a0, result		       # pega o tamanho da string resultante
		move 	$s1, $a0		       # salva o valor em $s0
		li 	$a3, '\n'		       # carrega o caracter de quebra de linha
    		
    		
    		j  	removeNewLine		       # Limpa a string1 da quebra de linha

printString:   	li  	$v0, 4           	       # Mostra a mensagem na tela
		la  	$a0, msgCat       	       # Pega o endereço da mensagem
		syscall
		
		li $v0, 4			       #imprime a string concatenada na tela
    		la $a0, result			    
    		syscall
 
    		j userInteraction	       		# Volta para o menu 
    		
 	
removeNewLine:
  		beqz $a1, copyFirstString		# Se chegar ao fim começa a cópia da string1
  		subu $a1, $a1, 1			# $a1 = $a1 -1
  		lb $a2, str1($a1)			# cópia do primeiro byte da string
  		bne $a2, $a3, removeNewLine             # se $a2 != $a3  continua o loop
  		li $a3, 0				# $a3 = 0 
  		sb $a3, str1($a1)			# Salva o valor em $a3

copyFirstString:  
   		lb $t0, ($s2)                  		# Pega os caracteres em seu endereço
   		beqz $t0, copySecondString     		# Se $t0 == 0 começa a cópia da segunda strint
   		sb $t0, ($s1)                  		# Cópia o caracter atual em memória  
   		addi $s2, $s2, 1               		# Incrementa o ponteiro
   		addi $s1, $s1, 1               		# Incrementa o ponteiro da string final 
   		j copyFirstString              		# continua em loop
   
copySecondString:  
   		lb $t0, ($s3)                  		# Pega os caracteres em seu endereço
   		beqz $t0, printString	       		# Se $t0 == 0 imprime a string concatenada
   		sb $t0, ($s1)                  		# Cópia o caracter atual em memória   
   		addi $s3, $s3, 1               		# Incrementa o ponteiro
   		addi $s1, $s1, 1               		# Incrementa o ponteiro da string final  
   		j copySecondString             		# Continua o loop  
   
 

########################################### Fim do Bloco da Função StrCat ###########################################

########################################### Bloco da Função StrCpy ##################################################
strcpy:	
		li  	$v0, 4           	       #Interage com usuário para que ele informe a string
		la  	$a0, stringMessage             #Pega o endereço da mensagem
		syscall

		li 	$v0, 8		       	       # Salva o valor inserido no console
		la 	$a0, str1	               # salva o valor de str1 em $a0
		li 	$a1, 32	                       # informa o tamanho da string
		syscall
		
		la  	$a1, str2         	       # Carrega o ponteiro destino para a1
    		li      $v0, 0               	       # Número de ítens copiados = 0
    		
			
    	        addi 	$sp, $sp, -12                  # desloca 12 bytes para inserir 3 palavras na pilha
	        sw 	$a0, 0($sp)		       # empilha $a0 
	        sw 	$a1, 4($sp)		       # empilha $a1
	        sw 	$s0, 8($sp)     	       # empilha $s0
	
	        j loop
		

	
loop:
		lb $s1, 0($a0)				#  $s1 = primeiro caracter da string origem
		sb $s1, 0($a1)				#  memoria[a0] = $s1  (copia o caracter para a string destino)

		addi $a1, $a1, 1			#  incrementa endereco da string origem
		addi $a0, $a0, 1			#  incrementa endereco da string destino
	
	

		bne $s1, $zero, loop 			#  repita ate string origem encontrar o '\0'
	
		lw $a1, 0($sp)				# recupera $a0 original da pilha
		lw $a0, 4($sp)				# recupera $a1 original da pilha
		lw $s0, 8($sp)     			# recupera $s0 original da pilha
    		addi $sp, $sp, 12   			#  volta 12 bytes para retirar 3 palavras na pilha
		move $s0,$a1				# salva a string copiada
		j printStringCpy
	
printStringCpy: 
		li  $v0,4           			# Opção para imprimir uma string
		la  $a0,copia         			# Pega o endereço da String
		syscall
		
		li $v0, 4			        #imprime a string concatenada na tela
		move $a0,$s0
    				    
    		syscall
 
    		j userInteraction	       		# Volta para o menu 
    		
########################################### Fim do Bloco da Função StrCpy ###########################################

########################################### Bloco da Função StrCmp ##################################################
strcmp:
		li $v0,4
		la $a0,msg1
		syscall
		
		li $v0,8
		la $a0,str1
		addi $a1,$zero,32
		
		syscall
		
		li $v0,4
		la $a0,msg2
		syscall
		
		li $v0,8
		la $a0,str2
		addi $a1,$zero,32
		syscall   #got string 2

		la $a0,str1  #pass address of str1
		la $a1,str2  #pass address of str2
		jal strAux  #call strcmp
		
strAux: 	add $t0,$zero,$zero
		add $t1,$zero,$a0
		add $t2,$zero,$a1
		
loop3:
		lb $t3($t1)  #load a byte from each string
		lb $t4($t2)
		beqz $t3,checkt2 #str1 end
		beqz $t4,missmatch
		slt $t5,$t3,$t4  #compare two bytes
		bnez $t5,missmatch
		addi $t1,$t1,1  #t1 points to the next byte of str1
		addi $t2,$t2,1
		j loop3

missmatch: 
		addi $v0,$zero,1
		j endfunction
checkt2:
		bnez $t4,missmatch
		add $v0,$zero,$zero

endfunction:	
		move $a0,$v0
		li  $v0,1           			# Opção para imprimir uma string
		syscall

 
    		j userInteraction	       		# Volta para o menu 


########################################### Fim do Bloco da Função StrCmp ###########################################

########################################### Bloco da Função StrLwr ##################################################

strlwr:		li  	$v0, 4           	       	#Interage com usuário para que ele informe a string
		la  	$a0, stringMessageUpper         #Pega o endereço da mensagem
		syscall

		li 	$v0, 8		       	      	# Salva o valor inserido no console
		la 	$a0, str1	              	# salva o valor de str1 em $a0
		li 	$a1, 32	                      	# informa o tamanho da string
		syscall

		li $t0, 0			      	# $t0 = i
loop1:
		add $t1, $t0, $a0 		       	# $t1 = &str[i]
		lb $t2, 0($t1)    			# $t2 = str[i]
		beq $t2, $0, printLower 		# verifica se chegou ao fim da string
		blt $t2, 65,next 			# verifica se o caracter é menor do que 65, se for ele incrementa o ponteiro
		bgt $t2, 90, next 			# verifica se o caracter é maior do que 90, se for ele incrementa o ponteiro
		add $t2, $t2, 32 			# Basta somar 32 ao byte lido para realizar a conversão
		sb $t2, 0($t1) 				# Salva o byte convertido 
next:
		addi $t0, $t0, 1			# Incrementa o ponteiro
		j loop1					# Continua o Loop

printLower: 	
		move $s0,$a0
		li  $v0,4           			# Opção para imprimir uma string
		la  $a0,convertLow         		# Pega o endereço da String
		syscall
		
		li $v0, 4			        #imprime a string concatenada na tela
		move $a0,$s0
    				    
    		syscall
 
    		j userInteraction	       		# Volta para o menu 
						
		 
########################################### Fim do Bloco da Função StrLWr ###########################################

########################################### Bloco da Função Strupr ##################################################

strupr:		li  	$v0, 4           	       	#Interage com usuário para que ele informe a string
		la  	$a0, stringMessageLow           #Pega o endereço da mensagem
		syscall

		li 	$v0, 8		       	      	# Salva o valor inserido no console
		la 	$a0, str1	              	# salva o valor de str1 em $a0
		li 	$a1, 32	                      	# informa o tamanho da string
		syscall

		li $t0, 0			      	# $t0 = i
loop2:
		add $t1, $t0, $a0 		       	# $t1 = &str[i]
		lb $t2, 0($t1)    			# $t2 = str[i]
		beq $t2, $0, printUp		        # verifica se chegou ao fim da string
		blt $t2, 97,next1 			# verifica se o caracter é menor do que 97, se for ele incrementa o ponteiro
		bgt $t2, 122, next1 			# verifica se o caracter é maior do que 122, se for ele incrementa o ponteiro
		add $t2, $t2, -32 			# Basta subtrair 32 ao byte lido para realizar a conversão
		sb $t2, 0($t1) 				# Salva o byte convertido 
next1:
		addi $t0, $t0, 1			# Incrementa o ponteiro
		j loop2				        # Continua o Loop

printUp: 	
		move $s0,$a0
		li  $v0,4           			# Opção para imprimir uma string
		la  $a0,convertUp        	        # Pega o endereço da String
		syscall
		
		li $v0, 4			       #imprime a string convertida
		move $a0,$s0
    				    
    		syscall
 
    		j userInteraction	       		# Volta para o menu 

########################################### Fim do Bloco da Função Strupr ###########################################



