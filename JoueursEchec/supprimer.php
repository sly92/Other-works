<?php 
	require('connexion.php'); //Permet la connexion à la base de données
	require('debut.php'); //En-tête html
	require('fonctions.php'); //Ensemble de fonctions PHP
?>

<div class="filtre">
<?php 
	if(isset($_GET['nom']) && isset($_GET['prenom']) && joueurExiste($bd,$_GET['nom'],$_GET['prenom']) )
	{
?>

<form action="liste.php" method="post">
<p> Voulez-vous vraiment supprimer le joueur <?php echo $_GET['nom'] . ' ' .  $_GET['prenom'] ; ?> ?
<input type="hidden" name="nom" value="<?php echo $_GET['nom'];?>"/>
<input type="hidden" name="prenom" value="<?php echo $_GET['prenom'];?>"/></p>
<p><input type="submit" value="oui" name="suppression"/><input type="submit" value="non" name="suppression"/></p>
</form>

<?php
	}
	else
	{
?>

	<p> Problème : retourner à la <a href="liste.php">liste</a>.
<?php } ?>




</div>

<?php require('fin.php'); ?>
