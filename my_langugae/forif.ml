#tivI n
#mutq <- n
#
#tivI s = 1
#ete(n >= 0) ->
#    cikl (n != 0) ->
#        s = (s * n)
#        n = (n - 1)
#        ete (n == 1) ->
#            elq -> [hjnu]
#        <-
#    elq -> 1
#    <-
#    elq -> 1
#<-
#elq -> s


########example1########
tivI w
mutq <- w
tivI i = 1
cikl (i != (w + 1) ->
    tivI n = i
    ete(n > 0) ->
        cikl (n > 0) ->
            elq -> n
            n = (n - 1)
        <-
#elq -> s
    <-
    i = (i + 1)
 <-
