from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity

def compute_similarity(doc1, doc2):
    documents = [doc1, doc2]

    vectorizer = TfidfVectorizer()

    tfidf_matrix = vectorizer.fit_transform(documents)

    similarity = cosine_similarity(tfidf_matrix[0:1], tfidf_matrix[1:2])

    return similarity[0][0]

doc1 = "Text document one content here."
doc2 = "Text document one content here."

similarity_score = compute_similarity(doc1, doc2)
print(f"Similarity score between documents: {similarity_score:.4f}")
