// IDEA:
//
// Tenemos que contar el número de parcelas que están comprendidas
// dentro del ciclo.  Para que estén dentro del ciclo, partiendo de
// uno de los bordes del mapa, para llegar al punto de interés hemos
// tenido que cruzar el ciclo un NÚMERO IMPAR DE VECES. Por lo tanto,
// proponemos:
//
//  - Generar un "mapa" donde el ciclo esté marcado con 1-s y el resto
//    sean 0-s.
//
//  - Generar otro "mapa" con la suma entre el borde y cada punto.
//
//  - Contar el número de puntos en los que el segundo mapa sea impar
//    y no pertenezcan al ciclo.
//
// Estos tres pasos se pueden hacer en dos, juntando los dos últimos
// en un único ciclo FOR. 


