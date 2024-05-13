/*
Solucion TP de logico
Integrantes:
 - Valentina Thiwissen
 - Dana Bejarano
 - Pedro Mazzieri
 - Nicolas Kalaydjian
*/

% Punto 1)

es_carpincho(carpincho(kike, habilidades([saltar,correr]), atributos(100,50,40))).
es_carpincho(carpincho(nacho, habilidades([olfatear,saltar]), atributos(60,80,80))).
es_carpincho(carpincho(alancito, habilidades([correr]), atributos(80,80,70))).
es_carpincho(carpincho(gastoncito, habilidades([olfatear]), atributos(100,30,20))).
es_carpincho(carpincho(sofy, habilidades([saltar,correr,olfatear]), atributos(100,90,100))).
es_carpincho(carpincho(dieguito, habilidades([trepar,correr,saltar]), atributos(99,99,80))).
es_carpincho(carpincho(contu, habilidades([olfatear,lavar,contabilidadHogarenia,saltar]), atributos(60,70,60))).

% Punto 2)

disciplina(saltoConRamita,[habilidades([correr,saltar])]).
disciplina(armadoDeMadriguera,[atributos(70,0,0)]).
disciplina(huidaDeDepredador,[habilidades([correr,olfatear]), atributos(0,0,80)]).
disciplina(preparacionDeEnsalada,[habilidades([olfatear,saltar,contabilidadHogarenia])]).
disciplina(trepadaDeLigustrina,[habilidades([saltar,trepar,correr])]).
disciplina(invasionDeCasas,[atributos(50,90,0)]).
disciplina(revolverBasura,[habilidades([olfatear,correr]), atributos(0,0,50)]).
disciplina(cebarMate,[habilidades([olfatear]), habilidadesNoPermitidas([lavar])]).

% Punto 3)

disciplinaDificil(Disciplina):-
    disciplina(Disciplina, Restricciones),
    cumpleRequisitos(Restricciones).
   
cumpleRequisitos(Restricciones):-
    member(habilidades(Habilidades),Restricciones),
    length(Habilidades,Cantidad),
    Cantidad > 2.

cumpleRequisitos(Restricciones):-
    member(atributos(Fuerza,Destreza,Velocidad),Restricciones),
    Suma is Fuerza + Destreza + Velocidad,
    Suma>100.

% Punto 4)

puedeRealizar(Nombre, Disciplina):-
    disciplina(Disciplina, Restricciones),
    es_carpincho(carpincho(Nombre, _, _)),
    forall(member(Restriccion, Restricciones), cumpleRestriccion(Nombre, Restriccion)).

cumpleRestriccion(Nombre, habilidades(HabilidadesMinimas)):-
    es_carpincho(carpincho(Nombre, habilidades(HabilidadesCarpincho), _)),
    forall(member(HabilidadMinima, HabilidadesMinimas), member(HabilidadMinima, HabilidadesCarpincho)).

cumpleRestriccion(Nombre, habilidadesNoPermitidas(HabilidadesNoPermitidas)):-
    es_carpincho(carpincho(Nombre, habilidades(HabilidadesCarpincho),_)),
    forall(member(HabilidadCarpincho, HabilidadesCarpincho), not(member(HabilidadCarpincho, HabilidadesNoPermitidas))).

cumpleRestriccion(Nombre, atributos(FuerzaMin, DestrezaMin, VelMin)):-
    es_carpincho(carpincho(Nombre, _, atributos(Fuerza, Destreza, Velocidad))),
    Fuerza >= FuerzaMin,
    Destreza >= DestrezaMin,
    Velocidad >= VelMin.

% Punto 5)

carpinchoExtranio(Nombre):-
    es_carpincho(carpincho(Nombre, _, _)),
    forall(puedeRealizar(Nombre, Disciplina), disciplinaDificil(Disciplina)).

% Punto 6)

carpinchoGanador(Carpincho1,Carpincho2,Disciplina,CarpinchoGanador):-
    Carpincho1 = carpincho(Nombre1, _, _),
    Carpincho2 = carpincho(Nombre2, _, _),
    CarpinchoGanador = carpincho(Ganador, _, _),
    es_carpincho(Carpincho1),
    es_carpincho(Carpincho2),
    es_carpincho(CarpinchoGanador),
    disciplina(Disciplina, _), 
    Nombre1 \= Nombre2,
    quienGana(Nombre1,Nombre2,Disciplina,Ganador).

quienGana(Nombre1,Nombre2,Disciplina,Ganador):-
    puedeRealizar(Nombre1,Disciplina),
    puedeRealizar(Nombre2,Disciplina),
    desempate(Nombre1,Nombre2,Ganador).

quienGana(Nombre1,Nombre2,Disciplina,Nombre1):-
    puedeRealizar(Nombre1,Disciplina),
    not(puedeRealizar(Nombre2,Disciplina)).

quienGana(Nombre1,Nombre2,Disciplina,Nombre2):-
    puedeRealizar(Nombre2,Disciplina),
    not(puedeRealizar(Nombre1,Disciplina)).

desempate(Nombre1,Nombre2,Ganador):-
    es_carpincho(carpincho(Nombre1,_,atributos(F1,D1,V1))),
    es_carpincho(carpincho(Nombre2,_,atributos(F2,D2,V2))),
    Suma1 is F1+D1+V1,
    Suma2 is F2+D2+V2,
    ganador(Suma1,Suma2,Nombre1,Nombre2,Ganador).

ganador(Suma1,Suma2,Nombre1,_,Nombre1):-
    Suma1 > Suma2.

ganador(Suma1,Suma2,_,Nombre2,Nombre2):-
    Suma2 > Suma1.

% Punto 7

atributosCarpincho(Carpincho, F, D, V):-
    Carpincho = carpincho( _ , _ , atributos(F, D, V)).

pesasCarpincha(Peso, Carpincho1, Carpincho2):-
    atributosCarpincho(Carpincho1, F1, D, V),
    atributosCarpincho(Carpincho2, F2, D, V),
    F2 is F1 + Peso * (0.25).

atrapaLaRana(Cantidad, Carpincho1, Carpincho2):-
    atributosCarpincho(Carpincho1, F, D1, V),
    atributosCarpincho(Carpincho2, F, D2, V),
    D2 is D1 + Cantidad.

cardiopincho(Km, Carpincho1, Carpincho2):-
    atributosCarpincho(Carpincho1, F, D, V1),
    atributosCarpincho(Carpincho2, F, D, V2),
    V2 is V1 + 2 * Km.

carssfit(Minutos, Carpincho1, Carpincho2):-
    atributosCarpincho(Carpincho1, F1, D1, V1),
    atributosCarpincho(Carpincho2, F2, D2, V2),
    F2 is F1 + Minutos,
    D2 is D1 + Minutos,
    V2 is V1 - 2 * Minutos.

% Punto 8)

aCuantosLesGana(NombreGanador,Disciplina,CantidadPerdedores):-
    disciplina(Disciplina,_),
    CarpinchoGanador = carpincho(NombreGanador,_,_),
    es_carpincho(CarpinchoGanador),
    findall(CarpinchoPerdedor, ((carpinchoGanador(CarpinchoGanador,CarpinchoPerdedor,Disciplina,CarpinchoGanador) , es_carpincho(CarpinchoPerdedor)), CarpinchoPerdedor \= CarpinchoGanador),CarpinchosPerdedores),
    length(CarpinchosPerdedores,CantidadPerdedores).

% Punto 9)

laRompeEn(Disciplina,NombreCarpincho):-
    disciplina(Disciplina,_),
    CarpinchoQueLaRompe = carpincho(NombreCarpincho,_,_),
    es_carpincho(CarpinchoQueLaRompe),
    forall((es_carpincho(CarpinchoPerdedor), CarpinchoPerdedor \= CarpinchoQueLaRompe), carpinchoGanador(CarpinchoQueLaRompe, CarpinchoPerdedor, Disciplina, CarpinchoQueLaRompe)).

% Punto 10)

drimTim(Disciplinas, DrimTim):-
    maplist(laRompeEn,Disciplinas,DrimTimgenerado),
    list_to_set(DrimTimgenerado,DrimTim).