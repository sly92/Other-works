<?php 
	require('connexion.php'); //Permet la connexion à la base de données
	require('debut.php'); //En-tête html
	require('fonctions.php'); //Ensemble de fonctions PHP
?>



<?php
	//Suppression d'un joueur (?)
	$paramPost = array('suppression','nom','prenom');
	if(testParam($paramPost,$_POST) && $_POST['suppression']=='oui')
	{
		//On teste si le joueur existe
		if(joueurExiste($bd,$_POST['nom'],$_POST['prenom']))
		{
			//On le supprime
			try
			{
				$req = $bd->prepare('DELETE from joueursEchec WHERE Nom = :nom AND Prénom = :prenom');
				$req->bindValue(':nom',$_POST['nom']);
				$req->bindValue(':prenom',$_POST['prenom']);
				$req->execute();
				
			}
			catch(PDOException $e)
			{
				die('<div class="filtre"> Erreur : ' . $e->getMessage() . '</div></body></html>');
			}
		}
	}

	//Préparation du classement par nom ou score
	if(isset($_GET['ordre']) and $_GET['ordre']=='Nom')
		$ordre = 'Nom';
	else
		$ordre = 'Score';	
?>



<div class="filtre">
	<form action="<?php echo $_SERVER['PHP_SELF']; ?>">
		<p> Année de naissance : 
			<select name="signeNaissance">
				<option value="-1"> &le; </option>
				<option value="0"> == </option>
				<option value="1"> &ge; </option>
			</select>
			<input type="text" name="naissance"/> Pays :
			<select name="pays">
				<option value="tous" selected="selected"> --- </option>
				<?php genereOptionsSelectPays($bd); ?>
			</select> 
			<input type="hidden" name="ordre" value="<?php echo $ordre; ?>"/>
			<input type="submit" value="Filtrer"/>
		</p>
	</form>
	<p class="droite">Trier par : <a href="<?php genereUrl('Score');?>">score</a>  <a href="<?php genereUrl('Nom');?>">nom</a></p>
</div>




<?php
	
//Préparation des valeurs de fitres pour l'affichage
$filtres = array();

if(isset($_GET['naissance']) && isset($_GET['signeNaissance']) && isset($_GET['pays']))
{
	$_GET['naissance'] = intval($_GET['naissance']);
	$_GET['signeNaissance'] = intval($_GET['signeNaissance']);
	//Si les paramètres naissance et signeNaissance sont bons
	if($_GET['naissance'] >= 1900 && $_GET['naissance'] <= 2010 && $_GET['signeNaissance'] >= -1 && $_GET['signeNaissance'] <= 1)
	{	
		$filtres[':naissance'] = $_GET['naissance'];
		$filtres[':signeNaissance'] = $_GET['signeNaissance'];
	}
	
	//Le pays est renseigné
	if(trim($_GET['pays']) != '' and $_GET['pays']!='tous')
		$filtres[':pays'] = $_GET['pays'];
}

?>





<div class="resultat">
	<?php afficheJoueursSelonFiltre($bd,$filtres,$ordre); ?>
</div>

<?php require('fin.php'); ?>
