import streamlit as st
from transformers import BartTokenizer, BartForConditionalGeneration

model_name = 'facebook/bart-large-cnn'
model = BartForConditionalGeneration.from_pretrained(model_name)
tokenizer = BartTokenizer.from_pretrained(model_name)

st.title("Document Summarization App")

document = st.text_area("Enter the document you want to summarize", height=300)

def summarize_text(doc):
    inputs = tokenizer.encode("summarize: " + doc, return_tensors="pt", max_length=1024, truncation=True)
    summary_ids = model.generate(inputs, max_length=150, min_length=40, length_penalty=2.0, num_beams=4, early_stopping=True)
    summary = tokenizer.decode(summary_ids[0], skip_special_tokens=True)
    return summary

if st.button("Summarize"):
    if document:
        with st.spinner("Summarizing..."):
            summary = summarize_text(document)
        st.subheader("Summary")
        st.write(summary)
    else:
        st.error("Please enter a document to summarize.")
