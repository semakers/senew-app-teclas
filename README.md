# senew-app-teclas — Teclas

*Español más abajo — [ir a la versión en español](#español).*

> [!WARNING]
> **senew is a new project; use it at your own risk.** The apps, the system and the tools are young software for a discontinued phone.
> Back up your phone before installing anything and expect rough edges.

Key tester: draws the real 6x5 keypad matrix (plus the five ground keys), read raw 25 times a second. Hold Back for a second to leave. Walkman, Play and volume keys can be tested here too.

This is an app (`.sen`) for **[senew](https://github.com/semakers/senew-w580)**, the open operating system for the Sony Ericsson W580i
(see <https://semakers.com>). It is written against the public API of **[senew-sdk](https://github.com/semakers/senew-sdk)**.

## Build

You need an `arm-none-eabi-gcc` toolchain (Arm GNU Toolchain 15.x tested), GNU make, Python 3.8+ and git.

```sh
git clone https://github.com/semakers/senew-app-teclas
cd senew-app-teclas
make              # -> build/teclas.sen
```

The Makefile looks for the SDK next to this folder (`../senew-sdk`) and, if it is not there, clones it into `./.senew-sdk` the first time.
To use another copy: `make SENEW_SDK=/path/to/senew-sdk`. Everything about the toolchain and the API is in the SDK's documentation.

## Install

Open **SENUS** with the phone connected, go to **Apps** and use **"Subir .sen"** (upload a .sen) to put `build/teclas.sen` on the phone.

## License

MIT — see [`LICENSE`](LICENSE). The comments in the sources are in Spanish (the project's working language).
Sony Ericsson, W580i and other names are trademarks of their respective owners and are used only to say which hardware this is about; this project is not affiliated with them.

---

<a id="español"></a>

# senew-app-teclas — Teclas

> [!WARNING]
> **senew es un proyecto nuevo; úsalo bajo tu propio riesgo.** Las apps, el sistema y las herramientas son software joven para un teléfono descatalogado.
> Haz una copia de seguridad del teléfono antes de instalar nada y cuenta con asperezas.

Probador del teclado: pinta la matriz real de 6x5 (más las cinco teclas a masa), leída en crudo 25 veces por segundo. Mantén «Atrás» un segundo para salir. Aquí también se prueban Walkman, Play y el volumen.

Esta es una app (`.sen`) para **[senew](https://github.com/semakers/senew-w580)**, el sistema operativo abierto del Sony Ericsson W580i
(ver <https://semakers.com>). Está escrita contra la API pública de **[senew-sdk](https://github.com/semakers/senew-sdk)**.

## Compilar

Necesitas una cadena `arm-none-eabi-gcc` (probada la Arm GNU Toolchain 15.x), GNU make, Python 3.8+ y git.

```sh
git clone https://github.com/semakers/senew-app-teclas
cd senew-app-teclas
make              # -> build/teclas.sen
```

El Makefile busca el SDK junto a esta carpeta (`../senew-sdk`) y, si no está, lo clona en `./.senew-sdk` la primera vez.
Para usar otra copia: `make SENEW_SDK=/ruta/a/senew-sdk`. Todo sobre la cadena de herramientas y la API está en la documentación del SDK.

## Instalar

Abre **SENUS** con el teléfono conectado, entra en **Apps** y usa **«Subir .sen»** para poner `build/teclas.sen` en el teléfono.

## Licencia

MIT — ver [`LICENSE`](LICENSE). Los comentarios de los fuentes están en español (la lengua de trabajo del proyecto).
Sony Ericsson, W580i y otros nombres son marcas de sus respectivos dueños y se usan solo para decir de qué aparato se trata; este proyecto no tiene relación con ellos.
