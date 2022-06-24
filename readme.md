# LojaC

Projeto antigo entregue como trabalho final da disciplina "Programação Estruturada". Ele gerencia os clientes e as compras de uma loja fictícia. Foi feito em conjunto com [Rayanne Ellen Lopes Ferreira](https://github.com/RayanneLps). Infelizmente, não tenho mais o estudo de caso que descrevia a loja e seus requisitos. Honestamente, eu fiz umas coisas nesse código que são de doer o coração, como as várias funções auxiliares, que acabaram mais atrapalhando do que ajudando. 

Cada menu segue a mesma estrutura lógica com 3 funções básicas: uma função exibe as operações do menu, outra requisita uma operação para o usuário e a última processa a operação escolhida(invocando a função desejada). Essas 3 funções ficam alojadas em um loop para que o usuário retorne ao menu após fazer o que deseja. 

Os dados dos clientes foram organizados em structs e armazenados em arrays.

Pra eliminar o uso de variáveis globais, o programa usa ponteiros em praticamente todo lugar, a fim de "movimentar as variáveis através dos menus e operações".

## Screenshots

Entrando e saindo de um menu.

![screenshot 1](img/screenshot1.png)

Cadastrando clientes.

![screenshot 2](img/screenshot2.png)

Listando clientes cadastrados.

![screenshot 3](img/screenshot3.png)

Encerrando o programa.

![screenshot 4](img/screenshot4.png)