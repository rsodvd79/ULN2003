# ULN2003 + 28BYJ‑48 con Arduino (PlatformIO)

Piccolo progetto per pilotare un motore passo‑passo 28BYJ‑48 tramite la scheda driver ULN2003 usando un Arduino UNO e la libreria `Stepper`.

Il programma corrente fa avanzare il motore di 1 passo alla volta a 15 RPM; sono presenti esempi (commentati) per fare una rotazione completa in entrambi i versi.

## Hardware necessario

- Arduino UNO (o compatibile)
- Motore passo‑passo 28BYJ‑48 (5V)
- Driver ULN2003
- Cavi Dupont
- Alimentazione 5V (consigliata esterna; massa in comune con Arduino)

## Collegamenti (wiring)

Colori dei fili del motore 28BYJ‑48 e mappatura verso gli ingressi della ULN2003 e i pin Arduino usati dal progetto:

- IN1 (ULN2003) ← D7 Arduino — filo Blu
- IN2 (ULN2003) ← D6 Arduino — filo Rosa
- IN3 (ULN2003) ← D5 Arduino — filo Giallo
- IN4 (ULN2003) ← D4 Arduino — filo Arancione
- VCC ULN2003 → 5V (meglio da alimentatore esterno)
- GND ULN2003 → GND comune con Arduino e alimentatore

Nota: la libreria `Stepper` per questo motore richiede l’ordine di inizializzazione dei pin come nel codice (`OUTPUT1, OUTPUT3, OUTPUT2, OUTPUT4`), anche se il cablaggio resta IN1→D7, IN2→D6, IN3→D5, IN4→D4.

## Software / Configurazione

- Piattaforma: PlatformIO su VS Code
- Board: `uno`
- Framework: `arduino`
- Libreria: `arduino-libraries/Stepper@^1.1.3`

Il file `platformio.ini` è già configurato:

```
[env:uno]
platform = atmelavr
board = uno
framework = arduino
lib_deps = arduino-libraries/Stepper@^1.1.3
```

## Come usare

1. Collega Arduino e seleziona la porta seriale in PlatformIO.
2. Compila e carica il firmware sulla scheda.

Il programma non stampa nulla su Serial Monitor (non è necessario aprirlo).

## Logica del codice principale

- `stepsPerRotation = 2048` per 28BYJ‑48 in modalità full‑step (1 rotazione ≈ 2048 passi). 
- `myStepper.setSpeed(15)` imposta 15 RPM.
- Nel `loop()` viene eseguito `myStepper.step(1)` per avanzare continuamente di un singolo passo.

Per fare una rotazione completa o invertire il verso, scommenta gli esempi presenti in `src/main.cpp`:

- Rotazione completa in avanti: `myStepper.step(stepsPerRotation);`
- Rotazione completa indietro: `myStepper.step(-stepsPerRotation);`

Suggerimenti:
- Aumenta/diminuisci `setSpeed(...)` per variare la velocità (RPM).
- Se il motore vibra ma non gira, ricontrolla l’ordine dei pin e l’alimentazione (preferisci 5V esterni con massa comune).
- Se usi half‑step con altre librerie/sequenze, i passi per giro possono diventare 4096.

## Troubleshooting rapido

- Vibra ma non ruota: ordine dei pin errato o fili scambiati.
- Perde passi a velocità alte: riduci RPM o usa alimentazione più stabile.
- Si scalda il driver: lascia pause tra rotazioni o abbassa la velocità.

Buon hacking con il tuo stepper 28BYJ‑48! 🚀
