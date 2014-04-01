import java.util.Date;

public interface Fichiers extends Iterable<Fichiers>, Visitable{

	int getTaille();
	String getNom();
	Date getDate();
}
