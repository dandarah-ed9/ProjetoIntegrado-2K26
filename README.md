# ProjetoIntegrado-2K26.

# Link do vídeo:
<https://youtu.be/9xxjDiH5ano?si=Toga8hLEbTBPm5q2>

---

## Objetivo:
Desenvolver um sistema embarcado interativo para controle de aulas em laboratório, utilizando microcontrolador STM32, display e botoeiras, integrando conceitos de lógica de programação, controle de estados, interface homem-máquina e organização de software embarcado. O projeto deve simular um fluxo real de controle de presença e gestão de alunos durante uma aula, modelando as regras, eventos e restrições operacionais típicas de sistemas reais.

---

# Como usar o programa</h1>
### Inicializando
O display irá exibir uma mensagem de boas vindas e indicará para apertar o botão PA10
para iniciar a aula
### Sistema de autentificação
Uma senha de 2 digitos será sorteada e deverá ser vista após o debug.

```c
  senha = (rand()% 99) + 1;
```

### Inserindo a senha
O professor irá digitar a senha através dos botões PA09 (dezena) e PA11 (unidade)
<table>
  <tr>
    <th> Quantidade de cliques</th>
    <th>Valor exibido</th>
  </tr>
  <tr> <td>1</td> <td>1</td> </tr>
  <tr> <td>2</td> <td>2</td> </tr>
  <tr> <td>3</td> <td>3</td> </tr>
  <tr> <td>4</td> <td>4</td> </tr>
  <tr> <td>5</td> <td>5</td> </tr>
  <tr> <td>6</td> <td>6</td> </tr>
  <tr> <td>7</td> <td>7</td> </tr>
  <tr> <td>8</td> <td>8</td> </tr>
  <tr> <td>9</td> <td>9</td> </tr>
  <tr> <td>10</td> <td>0</td> </tr>
</table>

### Validação
O programa irá multiplicar o digito inserido por PA9 e multiplicará por 10 e somará com o digitado pelo PA11, em seguida o subtrai pela senha.
```c
  verificacao = senha - (digito1 * 10 + digito2);
```
Se o número digitado for igual a senha irá aparecer "Acesso permitido" e passará para a próxima etapa.
Se o número for diferente irá zerar os dois digitos e aparecerá "Senha incorreta"

```c
  if (verificacao == 0){
    ST7789_WriteString(0, 200, "Acesso permitido", Font_11x18, GREEN, YELLOW);
    senha = 0;
  }
  else {
    ST7789_WriteString(0, 200, "Senha incorreta", Font_11x18, RED, YELLOW);
    digito1 = 0;
    digito2 = 0;
  }
```
