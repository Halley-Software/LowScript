# LowScript

Low level language with JavaScript/TypeScript syntax.

## Goals

The goal of LowScript is be a tiny programming language with a familiar syntax for everyone and provide to LowScript programs a simple but thorough standard library, avoiding the necessity of install thrid-party modules.

LowScript was born with the idea of ​​taking JavaScript to the low level. This is due to the simplicity of writing the latter, but the lack of low-level features, which meant that JavaScript could not go outside its environment, beyond backend and frontend applications (with some exceptions).
Just imagine being able to use references to a string or other primitive type, while still retaining the possibility of writing objects literally, as well as benefiting from the powerful prototype system that JavaScript offers. It would be something that in many cases would make the work much easier.

That is why I thought that a language that complied with the above mentioned, could end up fitting and feeling good to both novice and experienced users.

Another problem, which I personally didn't like about JavaScript, was having a standard library that wasn't common across all JavaScript engines and runtimes, where each one provide its own version of a feature. That's why LowScript has the `std` module. It provides most of the functionality needed for a common program.

> Clarification: When I say _-its own version-_ I don't mean a different implementation of _X_ class or function, but following the same rules, like the `globalThis` object, specified in ECMA-262.
>
> For example: all JavaScript-based **engines** (ECMA-262) define the `String.prototype.at` method in the same way. However, no **runtime** is subject to a specification and the extra functionality varies between each one.</br>
> For example: all runtimes allow JavaScript to read a file, but each one defines this functionality in the way that is considered most efficient or convenient for the runtime in which this functionality is being defined.

## Some basic concepts

Each LowScript program is structured with a system of packages and modules in order to make each project scalable and easy to manage.

When you create a LowScript project, all the source code is inside a folder called `src`. Within this, each folder is called a `package`, where each file is known as a `module`. Each of them, both packages and modules, can contain within itself other elements of the same type. That is, each `package` can contain other `packages` and each `module` can contain other `modules`. Let's see it with an example:

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

> File and folder tree mapping thanks to the Visual Studio Code extension: file-tree-generator

From the previous listing, we can see that each package is a container for modules. And each one can contain other packages.

The concept of packages ends there. You can see in the official tutorial that they are a vital part of importing modules, on our website: https://lowscript.our_site.domain/.

Now we will focus on modules, which are a bit more complex.

Each module contains executable code, but it cannot contain any type of code. Let's see:

Each module distinguishes between 2 types of _entities_, primary entities and any other type of entities.

Primary entities are:

- `modules`
- `functions`
- `classes`
- `interfaces`
- `type declarations`
- `constants`
- `enumerations`

> When modules are mentioned, we mean that a module can contain others, using the keyword `module` followed by a name.

Each of these entities represents a type of value and serves different purposes. In addition, each of them can only be declared within other primary entities. Except for functions, which can be declared within other functions or assigned to variables or constants. This feature is known as **first-level citizens**

The other type of entities, which cannot be declared in modules, but within other entities, whose body can be executable. These are: variables whose value can change (unlike constants, whose value is immutable, with a small exception, which is explained in our official tutorial), control structures, among others, which are specified in the official documentation page.

> When we refer to entities with an executable body, we refer to entities whose content is capable of returning a value once they are analyzed by the interpreter or compiler.

This differentiation has also been implemented to avoid _global variables_ as much as possible. Although these types of variables can be very convenient to use in small projects, if the project you are working on is too large, they can cause more problems than conveniences. This is because they can be modified in a certain part of the code, until reaching a certain point, you lose track of the modifications that the variable has suffered. Causing you to lose valuable time trying to find where it was modified.

![LowScriptLogo](./LowScriptLogo.jpg)
