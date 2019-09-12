                              #******************************#
                              #*			  Projet R		        *#
                              #*					  		            *#
                              #******************************#

library(rmarkdown)

# *** Exercice 1 *** #


## Creation des donnees 

# On prend la moyenne de chaque intervalle
CA <- c(0.125, 0.375, 0.75, 1.75, 3.75, 7.50)
CA

# Labels pour la droite des abscisses
names(CA) <- c("[0,0.25[","[0.25,0.5[","[0.5,1[","[1,2.5]","[2.5,5[","[5,10[")

# Effectif des entreprises pour chaque intervalle
nb_entreprises <- c(137, 106, 112, 154, 100, 33)
nb_entreprises


# 1)
# Calcule du chiffre d'affaire et de l'ecart type de la serie
meanCA <- mean(CA*nb_entreprises)
meanCA
sum_entreprises <- sum(nb_entreprises)
sum_entreprises
ecart_type <- sd(CA)*sqrt((sum_entreprises-1)/sum_entreprises)
ecart_type


# 2)
# Construction de l'histogramme des frequences 
hist(CA)


# 3) 
# Construction du polygones croissant des frequences cumulees
fc = cumsum(nb_entreprises)
plot(CA,fc,type="l", main="polygone des frequences cumulees croissant",xlab="chiffre d'affaire moyen", ylab="nombre d'entreprises")

# Construction du polygones decroissant des frequences cumulees
nb_entreprises2 <- c(sum_entreprises, -nb_entreprises[6], -nb_entreprises[5], -nb_entreprises[4], -nb_entreprises[3], -nb_entreprises[2])
fc2 = cumsum(nb_entreprises2)
plot(CA,fc2,type="l", main="polygone des frequences cumulees decroissant",xlab="chiffre d'affaire moyen", ylab="nombre d'entreprises")


# 4)
# Calcul de la mediane
median(CA)

# Determination de manière empirique de la proportion d'entreprise dont CA > 3M
abline(v=3)
abline(h=285)

proportion_entreprise = 285/sum_entreprises

print(paste("La proportion d'entreprise dont le chiffre d'affaire est supèrieur à 3 millions d'euros est de près de", proportion_entreprise))



# *** Exercice 2 *** #

## Creation des donnees 

# 1,2)
# import des donnees
data <- read.table("donnees/data3.txt", sep=" ", header=TRUE, fill = TRUE)

# 3)
meantab <- c(mean(data$x1), mean(data$x2) ,mean(data$x3) ,mean(data$x4),mean(data$y1) ,mean(data$y2), mean(data$y3), mean(data$y4))  
vartab <- c(var(data$x1), var(data$x2) ,var(data$x3) ,var(data$x4),var(data$y1) ,var(data$y2), var(data$y3), var(data$y4))  

# 4)
covtab <- c(cov(data$x1,data$y1),cov(data$x2,data$y2),cov(data$x3,data$y3),cov(data$x4,data$y4))
cortab <- c(cor(data$x1,data$y1),cor(data$x2,data$y2),cor(data$x3,data$y3),cor(data$x4,data$y4))

# 5)
plot(data$x1,data$y1)
plot(data$x2,data$y2)
plot(data$x3,data$y3)
plot(data$x4,data$y4)

# 6)
centered.data.x1 <- scale(data$x1, scale = FALSE)
centered.data.y1 <- scale(data$y1, scale = FALSE)

mean.scaled.x1 <- mean(centered.data.x1)
mean.scaled.y1 <- mean(centered.data.y1)

var.scaled.x1 <- var(centered.data.x1)
var.scaled.y1 <- var(centered.data.y1)

cor.scaled.x1 <- cor(centered.data.x1)
cov.scaled.y1 <- cov(centered.data.y1)

plot(centered.data.x1,centered.data.y1)




# *** Exercice 3 *** #

## Creation des donnees 

annee <- c(1:7)
indice <- c(165,176,193,202,222,245,253)

# 1)
plot(annee,indice)

# 2)
donnees <- data.frame(annee, indice)
reg<-lm(indice ~ annee, data=donnees)
coeff=coefficients(reg)

# Equation de la droite de regression : 
equation_droite = paste0("y = ", round(coeff[2],1), "*x ", round(coeff[1],1))

# Graphe
plot(indice, main=equation_droite)
abline(reg, col="blue")

# Cette formule nous renvois les coefficient a et b de l'equation de la droite (ax +b)
lm(indice ~ annee)
a <- 15.39
b <- 146.43

# 3)
# on remplace x par 9 dans l'équation de la droite de regréssion linéaire pour trouver l'indice de l'annee 9

indice_9 <- (a*9)+b
indice_9




# Exercice 4 #

# 1)
data <- read.table("donnees/exo4.txt", sep="\t", header=TRUE)

data

DF1 <- data.frame(data[0],data[1:10])
DF1
cor(DF1)

# 2) Il faut regarder les valeurs fortement corrélées ( 90%): SEAN est fortement corrélé avec ENTR et SALLE
# COMM est peu corrélé avec RECE

# Tout d'abord, il faut noter qu'on considère une forte corrélation entre deux variables à partir de 0.90.
# Les variables fortement corrélées sont : 
  
#  La plus grosse corrélation est entre ENTR et RECE (1.0)
#-> Ici, on peut aisément dire que plus le nombre d'entrées d'un film augmente et la recette de celui ci augmente. 

# 3)

#Paris a une seule commune, un seul département, c'est pourquoi on peut observer que ses valeurs sont plus élevées que les autres.
#   De plus, c'est le deuxième département le plus peuplé (2 125 000 habitants)



# PARTIE 2

# On ne laisse que les variables que l'on souhaite étudier

DF2 <- data.frame(data[0],data[4:10])

DF2.scaled <- scale(DF2, center = TRUE, scale = TRUE)

cor_df2 <- cor(DF2.scaled)
round(cor_df2,2)
cor_df2
diag(res.cor)

library("factoextra")
library("FactoMineR")

res.pca <- PCA(DF2,  graph = FALSE)

res.pca$eig

cor_df2

res.eig<-eigen(cor_df2)
rn <- rownames(cor_df2)
rownames(res.eig$vectors) <- rn
colnames(res.eig$vectors) <- c("Dim1", "Dim2", "Dim3", "Dim4", "Dim5", "Dim6", "Dim7")
res.eig$vectors






get_eig(res.pca)

fviz_pca_var(res.pca, col.var = "black")

get_eig(res.ca)

fviz_pca_ind(res.pca)

DF3<-DF2/DF1$popu

DF1$popu
DF3

DF3.scaled <- scale(DF3, center = TRUE, scale = TRUE)

res.cor <- cor(DF3.scaled)
round(res.cor, 2)

res.eig <- eigen(res.cor)
res.eig

