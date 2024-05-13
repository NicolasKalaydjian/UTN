:- include(solucion).



:- begin_tests(punto3).

test("Trepada de Ligustrina es una disciplina dificil", nondet):-
    disciplinaDificil(trepadaDeLigustrina).

test("Invasion de casas es una disciplina dificil", nondet):-
    disciplinaDificil(invasionDeCasas).

test("Armado de Madriguera no es dificil", nondet):-
    not(disciplinaDificil(armadoDeMadriguera)).

test("Cuales son las disciplinas dificiles", 
    set(Disciplina = 
        [preparacionDeEnsalada,trepadaDeLigustrina,invasionDeCasas])
    ):-
    disciplinaDificil(Disciplina).

:- end_tests(punto3).



:- begin_tests(punto4).

test("Dieguito puede trepar ligustrina", nondet):-
    puedeRealizar(dieguito,trepadaDeLigustrina).

test("Kike no  puede revolver basura", nondet):-
    not(puedeRealizar(kike,revolverBasura)).

test("Sofy puede invadir casas", nondet):-
    puedeRealizar(sofy,invasionDeCasas).

test("Quien puede realizar armadoDeMadriguera", 
    set(Carpincho = 
        [kike, alancito, gastoncito, sofy, dieguito])
    ):-
    puedeRealizar(Carpincho,armadoDeMadriguera).

test("Que disciplinas puede realizar dieguito", 
    set(Disciplina = 
        [saltoConRamita, armadoDeMadriguera, trepadaDeLigustrina, invasionDeCasas])
    ):-
    puedeRealizar(dieguito,Disciplina).

:- end_tests(punto4).



:- begin_tests(punto5).

test("Contu es extrania"):-
    carpinchoExtranio(contu).

test("Nacho no es extranio"):-
    not(carpinchoExtranio(nacho)).

test("Cuales son los carpinchos extranios", 
    set(Carpincho = 
        [contu])
    ):-
    carpinchoExtranio(Carpincho).

:- end_tests(punto5).



:- begin_tests(punto6).

test("Quien gana entre Sofy y Contu en saltoConRamita",
    set(Ganador = [carpincho(sofy, habilidades([saltar,correr,olfatear]), atributos(100,90,100))])
    ):-
    carpinchoGanador(
        carpincho(sofy, habilidades([saltar,correr,olfatear]), atributos(100,90,100)),
        carpincho(contu, habilidades([olfatear,lavar,contabilidadHogarenia,saltar]), atributos(60,70,60)),
        saltoConRamita,
        Ganador).
% gana sofy porque contu no puede realizar saltoConRamita

test("Quien gana entre Nacho y Alancito en cebarMate",
    set(Ganador = [carpincho(nacho, habilidades([olfatear,saltar]), atributos(60,80,80))])
    ):-
    carpinchoGanador(
        carpincho(nacho, habilidades([olfatear,saltar]), atributos(60,80,80)),
        carpincho(alancito, habilidades([correr]), atributos(80,80,70)),
        cebarMate,
        Ganador).
% gana nacho porque alancito no puede realizar cebarMate

test("Quien gana entre Kike y Contu en revolverBasura", fail):-
    carpinchoGanador(
        carpincho(kike, habilidades([saltar,correr]), atributos(100,50,40)),
        carpincho(contu, habilidades([olfatear,lavar,contabilidadHogarenia,saltar]), atributos(60,70,60)),
        revolverBasura,
        _).
% falla porque ninguno la puede realizar

test("Quien gana entre Kike y Kike en armadoDeMadriguera", fail):-
    carpinchoGanador(
        carpincho(kike, habilidades([saltar,correr]), atributos(100,50,40)),
        carpincho(kike, habilidades([saltar,correr]), atributos(100,50,40)),
        armadoDeMadriguera,
        _).
% falla porque son el mismo carpincho, un carpincho no se puede ganar a si mismo

test("Quien gana entre Kike y Dieguito en saltoConRamita",
    set(Ganador = [carpincho(dieguito, habilidades([trepar,correr,saltar]), atributos(99,99,80))])
    ):-
    carpinchoGanador(
        carpincho(kike, habilidades([saltar,correr]), atributos(100,50,40)),
        carpincho(dieguito, habilidades([trepar,correr,saltar]), atributos(99,99,80)),
        armadoDeMadriguera,
        Ganador).
% gana Dieguito ya que ambos pueden realizarla y Dieguito tiene mas sumatoria de atributos

test("En que disciplinas le gana Sofy a Contu",
    set(Disciplina = [revolverBasura,huidaDeDepredador,saltoConRamita,armadoDeMadriguera,invasionDeCasas,cebarMate])
    ):-
    carpinchoGanador(
        carpincho(sofy, habilidades([saltar,correr,olfatear]), atributos(100,90,100)),
        carpincho(contu, habilidades([olfatear,lavar,contabilidadHogarenia,saltar]), atributos(60,70,60)),
        Disciplina,
        carpincho(sofy, habilidades([saltar,correr,olfatear]), atributos(100,90,100))).

test("A quien le gana Sofy en revolverBasura",
    set(Quien = [
        carpincho(kike, habilidades([saltar,correr]), atributos(100,50,40)),
        carpincho(nacho, habilidades([olfatear,saltar]), atributos(60,80,80)),
        carpincho(alancito, habilidades([correr]), atributos(80,80,70)),
        carpincho(gastoncito, habilidades([olfatear]), atributos(100,30,20)),
        carpincho(dieguito, habilidades([trepar,correr,saltar]), atributos(99,99,80)),
        carpincho(contu, habilidades([olfatear,lavar,contabilidadHogarenia,saltar]), atributos(60,70,60))])
    ):-
    carpinchoGanador(
        carpincho(sofy, habilidades([saltar,correr,olfatear]), atributos(100,90,100)),
        Quien,
        revolverBasura,
        carpincho(sofy, habilidades([saltar,correr,olfatear]), atributos(100,90,100))).    

:- end_tests(punto6).



:- begin_tests(punto7).

test("pesasCarpincha", nondet):-
    pesasCarpincha(40, carpincho(kike,habilidades([saltar,correr]),atributos(100,50,40)), carpincho(kike,habilidades([saltar,correr]),atributos(110.0,50,40))).

test("atrapaLaRana", nondet):-
    atrapaLaRana(20, carpincho(nacho,habilidades([olfatear,saltar]),atributos(60,80,80)), carpincho(nacho,habilidades([olfatear,saltar]),atributos(60,100,80))).

test("cardiopincho", nondet):-
    cardiopincho(5, carpincho(alancito,habilidades([correr]),atributos(80,80,70)), carpincho(alancito,habilidades([correr]),atributos(80,80,80))).

test("carssfit", nondet):-
    carssfit(10, carpincho(contu,habilidades([olfatear,lavar,contabilidadHogarenia,saltar]),atributos(60,70,60)), carpincho(contu,habilidades([olfatear,lavar,contabilidadHogarenia,saltar]),atributos(70,80,40))).

:- end_tests(punto7).



:- begin_tests(punto8).

test("A cuantos le gana nacho en cebarMate",
    set(CantidadPerdedores = [5])
    ):-
    aCuantosLesGana(nacho,cebarMate,CantidadPerdedores).

test("A cuantos le gana kike en saltoConRamita",
    set(CantidadPerdedores = [4])
    ):-
    aCuantosLesGana(kike,saltoConRamita,CantidadPerdedores).

test("A cuantos le gana sofy en revolverBasura",
    set(CantidadPerdedores = [6])
    ):-
    aCuantosLesGana(sofy,revolverBasura,CantidadPerdedores).

test("En que disciplina Sofy le gana a 6",
    set(QueDisciplina = [saltoConRamita, armadoDeMadriguera, huidaDeDepredador, invasionDeCasas, revolverBasura, cebarMate])
    ):-
    aCuantosLesGana(sofy,QueDisciplina,6).

test("Quien le gana a 6 en resolver basura",
    set(Quien = [sofy])
    ):-
    aCuantosLesGana(Quien,revolverBasura,6).

:- end_tests(punto8).



:- begin_tests(punto9).

test("En que disciplinas la rompe Sofy",
    set(Disciplina = [revolverBasura,huidaDeDepredador,saltoConRamita,armadoDeMadriguera,invasionDeCasas,cebarMate])
    ):-
    laRompeEn(Disciplina,sofy).

test("Quien la rompe en preparacionDeEnsalada",
    set(Quien = [contu])
    ):-
    laRompeEn(preparacionDeEnsalada,Quien).

test("Quien la rompe en trepadaDeLigustrina",
    set(Quien = [dieguito])
    ):-
    laRompeEn(trepadaDeLigustrina,Quien).

:- end_tests(punto9).



:- begin_tests(punto10).

test("Dream Team para revolverBasura y preparacionDeEnsalada",
    set(DrimTim = [[sofy,contu]])
    ):-
    drimTim([revolverBasura,preparacionDeEnsalada], DrimTim).

test("Dream Team para revolverBasura y huidaDeDepredador",
    set(DrimTim = [[sofy]])
    ):-
    drimTim([revolverBasura,huidaDeDepredador], DrimTim).

:- end_tests(punto10).