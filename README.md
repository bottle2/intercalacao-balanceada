# Ordenação Externa: Intercalacao Balanceada

É implementado três programas: `read`, `ordenador` e `write`. Segue suas assinaturas:

* `write` _arquivo_ _quantidade-de-numeros_
* `ordenador` _arquivo_ _arquivo-ordenado_
* `read` _arquivo_

`write` gera um arquivo com números aleatórios dentro.
`ordenador` ordena os números de um arquivo.
`read` verifica se os números em um arquivo estão ordenados.

## Uso

Requer uma pasta `files` para funcionar no diretório onde o programa é rodado.
Crie-a rodando:

```
$ mkdir files
```

Rodando `make test` provê um exemplo de uso, segue abaixo reproduzido:

```bash
$ ./write arq 40000000
$ ./organizador arq arq-ordenado
$ ./read arq-ordenado
```

Procure não fazer coisas bestas como tentar ordenar 500 MB de números usando 20 bytes.

## Compilação

Pode ser compilado usando o Makefile disponibilizado rodando:

```
$ make all
```

Para remover binários e outros arquivos gerados, basta rodar:

```
$ make clean
```

Naturalmente, definições podem ser passadas:

```
$ CFLAGS="-O2 -march=native -flto" make clean all
```

Não há receita para instalação.

## Autores

Feito por Bento Borges Schirmer e Thiago Rodrigues Silva.
