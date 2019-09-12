<?php 
	require('connexion.php'); //Permet la connexion à la base de données
	require('debut.php'); //En-tête html
	require('fonctions.php'); //Ensemble de fonctions PHP
?>


<?php

$param = array('nom','prenom','pays','score','naissance');

//Si $_POST contient les clés nom, prenom, pays, score et naissance et qu'il y a des valeurs associées
if(testParam($param,$_POST))
{
	//Les nombres saisis pour le score et la naissance sont corrects
	if( ((string) $_POST['score']) === ((string)(int) $_POST['score']) && //si $_POST['score'] correspond à une valeur entière
		((string) $_POST['naissance']) === ((string)(int) $_POST['naissance']) && //Si $_POST['naissance'] correspond à une valeur entière
		$_POST['score']>= 0 &&
		$_POST['naissance'] >= 1900 && 
		$_POST['naissance'] <= 2010)
	{
	
		//Si le joueur existe
		if(joueurExiste($bd,$_POST['nom'],$_POST['prenom']))
			$sql = 'UPDATE joueursEchec SET Pays = :pays, Score = :score, Naissance = :naissance WHERE Nom = :nom AND Prénom = :prenom';
		else
			$sql = 'INSERT INTO joueursEchec (Nom, Prénom,Pays, Score, Naissance) VALUES (:nom, :prenom, :pays, :score, :naissance)';
	
		try
		{
				$req = $bd->prepare($sql);
				$req->bindValue(':nom',htmlspecialchars($_POST['nom']));
				$req->bindValue(':prenom',htmlspecialchars($_POST['prenom']));
				$req->bindValue(':pays',htmlspecialchars($_POST['pays']));
				$req->bindValue(':score',htmlspecialchars($_POST['score']));
				$req->bindValue(':naissance',htmlspecialchars($_POST['naissance']));
				$req->execute();
		}
		catch(PDOException $e)
		{
			die('<div class="filtre"> Erreur : ' . $e->getMessage() . '</div></body></html>'); 
		}
		echo '<div class="filtre"> <p> Mise à jour de la base de données effectuée </p> </div>';
	}	
}
?>





<div class="resultat">

	<h2> Ajout ou modification d'un joueur </h2>
	<form action="<?php echo $_SERVER['PHP_SELF'];?>" method="post">
		<p><label> Nom : </label> <input type="text" name="nom" id="nom"/></p>
		<p><label> Prénom : </label> <input type="text" name="prenom" id="prenom"/></p>
		<p><label> Pays : </label><input type="text" name="pays" id="pays"/></p>
		<p><label> Score : </label> <input type="text" name="score" id="score"/></p>
		<p><label> Naissance : </label> <input type="text" name="naissance" id="naissance"/></p>
		<p> <input type="submit" /> </p>
	</form>
</div>

<?php require('fin.php'); ?>
