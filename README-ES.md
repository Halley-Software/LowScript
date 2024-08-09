# LowScript

## Metas

El objetivo de LowScript es ser un lenguaje de programación liguero y pequeño con una sintaxis familiar para todos y proporcionar a los programas LowScript una librería estándar sencilla pero completa, evitando la necesidad de instalar módulos de terceros.

LowScript nació con la idea de llevar JavaScript al bajo nivel. Esto se debe a la simplicidad de escritura de este último, pero a la falta de funcionalidades de bajo nivel, lo que hacía que JavaScript no pudiera salir de su entorno, más allá de aplicaciones backend y frontend (salvo algunas excepciones).
Imagínense poder utilizar referencias a una cadena u otro tipo primitivo, pero conservando la posibilidad de escribir objetos de forma literal, además de beneficiarse del potente sistema de prototipos que ofrece JavaScript. Sería algo que en muchos casos facilitaría mucho el trabajo.

Por eso pensé que un lenguaje que cumpliera con lo mencionado anteriormente, podría acabar encajando y sintiendo bien tanto a usuarios novatos como a usuarios experimentados.

Otro problema, que personalmente no me gustaba de JavaScript, era tener una librería estándar que no fuera común a todos los motores y runtimes de JavaScript, donde cada uno aporta su propia versión de una característica. Por eso LowScript tiene el módulo `std`. El cual proporciona la mayoría de la funcionalidad necesaria para un programa común.

> Aclaracion: Cuando digo _-su propia versión-_ no me refiero a una implementación diferente de la clase o función _X_, sino a seguir las mismas reglas, como el objeto `globalThis`, especificado en la ECMA-262.
>
> Por ejemplo: todos los **motores** basados ​​en JavaScript (ECMA-262) definen el método `String.prototype.at` de la misma manera. Sin embargo, ningún **runtime** está sujeto a una especificación y la funcionalidad extra varía entre cada uno.</br>
> Por ejemplo: todos los runtimes permiten a JavaScript leer un archivo, pero cada uno define esta funcionalidad de la manera que se considera más eficiente o conveniente para el runtime en el que se está definiendo esta funcionalidad.

## Algunos conceptos básicos

Cada programa LowScript está estructurado con un sistema de paquetes y módulos con el fin de hacer que cada proyecto sea escalable y fácil de gestionar.

Cuando creas un proyecto LowScript, todo el código fuente se encuentra dentro de una carpeta llamada `src`. Dentro de esta, cada carpeta se denomina `paquete`, donde cada archivo se conoce como `módulo`. Cada uno de ellos, tanto paquetes como módulos, pueden contener dentro de sí otros elementos del mismo tipo. Es decir, cada `paquete` puede contener otros `paquetes` y cada `módulo` puede contener otros `módulos`. Veámoslo con un ejemplo:

```txt
📦project-test
 ┣ 📂src
 ┃ ┣ 📂package1
 ┃ ┃ ┣ 📂package2
 ┃ ┃ ┃ ┗ 📜inner-module.low
 ┃ ┃ ┗ 📜module1.low
 ┃ ┗ 📜main.low
 ┗ 📜lpm.json
```

> Esquema de archivos y carpetas gracias a la extensión de Visual Studio Code: file-tree-generator

De la anterior imágen, hemos podido obeservar que cada un paquete es un contenedor de módulos. Y cada uno, puede contener otros paquetes.

El concepto de paquetes llega hasta ahí. Podrás ver en el tutorial oficial que son una parte vital de la importación de módulos, en nuestra página web: https://lowscript.nuestro_sitio.dominio/.

Ahora nos centraremos en los módulos, que son un poco más complejos.

Cada módulo contiene código ejecutable, pero no puede contener cualquier tipo de código. Veámoslo:
Cáda módulo distingue entre 2 tipos de _entidades_, entidades primarias y cualquier otro tipo de entidades.

Las entidades primarias son:

- `módulos`
- `funciones`
- `clases`
- `interfaces`
- `declaraciones de tipos`
- `constantes`
- `enumeraciones`

> Cuando se mencionan módulos es que nos referimos a que un módulo puede contener otros, usando la palabara clave `module` seguido de un nombre.

Cada una de estas entidades, representa un tipo de valores y sirven para cosas distintas. Además cada una de ellas solo puede ser declarada dentro de otras entidades primarias. A excepción de las funciones, las cuales pueden ser declaradas dentro de otras funciones o ser asignadas a variables o constantes. A esta característica se le conoce como **ciudadanos de primer nivel**

El otro tipo de entidades, las cuales no pueden ser declaradas en módulos, si no dentro de otras entidades, cuyo cuerpo pueda ser ejecutable. Son: variables cuyo valor puede cambiar (a diferencia de las constantes, cuyo valor es inmutable, con una pequeña excepción, que es explicada en nuestro tutorial oficial), estructuras de control, entre otras, que son especificadas en la página de documentación oficial.

> Cuando nos referimos a entidades con un cuerpo ejecutable, nos referimos a entidades las cuales su contenido es capaz de devolver un valor una vez son analizadas por el intérprete o el compilador.

También se ha implementado esta diferenciación para evitar las _variable globales_ en la medidad de lo posible. Pese a que este tipo de variables pueden llegar a ser muy cómodas de utilizar en proyectos pequeños, si el proyecto en el que se esta trabajando es demasiado grande, pueden llegar a ocasionar más problemas que comodidades. Esto debido a que pueden ser modificadas en cierta parte del código, hasta que llegando a cierto punto, pierdes el rastro de modificaciones que ha sufrido la variable. Ocasionando que pierdas valioso tiempo en intentar encontrar donde fue modificada.

![LowScriptLogo](./LowScriptLogo.jpg)
